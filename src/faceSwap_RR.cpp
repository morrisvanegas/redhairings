#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
 
using namespace cv;
using namespace std;

//Read points from text file
vector<Point2f> readPoints(string pointsFileName){
	vector<Point2f> points;
	ifstream ifs(pointsFileName);
    float x, y;
	int count = 0;
    while(ifs >> x >> y)
    {
        points.push_back(Point2f(x,y));

    }

	return points;
}

// Apply affine transform calculated using srcTri and dstTri to src
void applyAffineTransform(Mat &warpImage, Mat &src, vector<Point2f> &srcTri, vector<Point2f> &dstTri)
{
    // Given a pair of triangles, find the affine transform.
    Mat warpMat = getAffineTransform( srcTri, dstTri );
    
    // Apply the Affine Transform just found to the src image
    warpAffine( src, warpImage, warpMat, warpImage.size(), INTER_LINEAR, BORDER_REFLECT_101);
}


// Calculate Delaunay triangles for set of points
// Returns the vector of indices of 3 points for each triangle
static void calculateDelaunayTriangles(Rect rect, vector<Point2f> &points, vector< vector<int> > &delaunayTri){

	// Create an instance of Subdiv2D
    Subdiv2D subdiv(rect);

	// Insert points into subdiv
    for( vector<Point2f>::iterator it = points.begin(); it != points.end(); it++)
        subdiv.insert(*it);	        

	vector<Vec6f> triangleList;
	subdiv.getTriangleList(triangleList);
	vector<Point2f> pt(3);
	vector<int> ind(3);

	for( size_t i = 0; i < triangleList.size(); i++ )
	{
		Vec6f t = triangleList[i];
		pt[0] = Point2f(t[0], t[1]);
		pt[1] = Point2f(t[2], t[3]);
		pt[2] = Point2f(t[4], t[5 ]);

		if ( rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])){
			for(int j = 0; j < 3; j++)
				for(size_t k = 0; k < points.size(); k++)
					if(abs(pt[j].x - points[k].x) < 1.0 && abs(pt[j].y - points[k].y) < 1)						
						ind[j] = k;					

			delaunayTri.push_back(ind);
		}
	}
		
}


// Warps and alpha blends triangular regions from img1 and img2 to img
void warpTriangle(Mat &img1, Mat &img2, vector<Point2f> &t1, vector<Point2f> &t2)
{
    
    Rect r1 = boundingRect(t1);
    Rect r2 = boundingRect(t2);

    Rect roi = r1;
    
    
    cout << roi.width + roi.x << endl;
    cout << img1.cols << endl;
    cout << roi.height + roi.y << endl;
    cout << img1.rows << endl;
    
    // Offset points by left top corner of the respective rectangles
    vector<Point2f> t1Rect, t2Rect;
    vector<Point> t2RectInt;
    for(int i = 0; i < 3; i++)
    {

        t1Rect.push_back( Point2f( t1[i].x - r1.x, t1[i].y -  r1.y) );
        t2Rect.push_back( Point2f( t2[i].x - r2.x, t2[i].y - r2.y) );
        t2RectInt.push_back( Point(t2[i].x - r2.x, t2[i].y - r2.y) ); // for fillConvexPoly

    }
    
    // Get mask by filling triangle
    Mat mask = Mat::zeros(r2.height, r2.width, CV_32FC3);
    fillConvexPoly(mask, t2RectInt, Scalar(1.0, 1.0, 1.0), 16, 0);
    
    // Apply warpImage to small rectangular patches
    Mat img1Rect;
    img1(r1).copyTo(img1Rect);

    
    Mat img2Rect = Mat::zeros(r2.height, r2.width, img1Rect.type());
    
    applyAffineTransform(img2Rect, img1Rect, t1Rect, t2Rect);

    
    multiply(img2Rect,mask, img2Rect);
    multiply(img2(r2), Scalar(1.0,1.0,1.0) - mask, img2(r2));
    img2(r2) = img2(r2) + img2Rect;


    
    
}

float calcBlurriness( const Mat &src )
{
    Mat Gx, Gy;
    Sobel( src, Gx, CV_32F, 1, 0 );
    Sobel( src, Gy, CV_32F, 0, 1 );
    double normGx = norm( Gx );
    double normGy = norm( Gy );
    double sumSq = normGx * normGx + normGy * normGy;
    return static_cast<float>( 1. / ( sumSq / src.size().area() + 1e-6 ));
}



int main( int argc, char** argv)
{
    Mat src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    char* window_name = "Laplace Demo";
    
    int c;
    
    
	//Read input images
    string filename1 = argv[1];
    string filename2 = argv[2];
    
    Mat img1 = imread(filename1);
    Mat img2 = imread(filename2);
    Mat img1Warped = img2.clone();
    
    /// Convert the image to grayscale
    cvtColor( img1, src_gray, CV_BGR2GRAY );
    
    // Assess average BGR values
    Scalar avg_BGR, sigma_BGR;
    meanStdDev(img1, avg_BGR, sigma_BGR);
    cout << "avg BGR: " << avg_BGR << endl;

    //Assess blur
    cout << "blur: " << calcBlurriness(img1) << endl;
    float blurriness = calcBlurriness(img1);
	
    //Read points
	vector<Point2f> points1, points2;
	points1 = readPoints(filename1 + ".txt");
	points2 = readPoints(filename2 + ".txt");
    
    //Assess straightness
    cout << "left eye: " << points1[37].x << endl;
    cout << "left edge: " << points1[2].x << endl;
    cout << "right eye: " << points1[46].x << endl;
    cout << "right edge: " << points1[16].x << endl;
    
    double left_eye, right_eye, left_edge, right_edge;
    
    left_eye = points1[37].x;
    left_edge = points1[2].x;
    right_eye = points1[46].x;
    right_edge = points1[16].x;
    
    double ratio;
    
    ratio = (left_eye - left_edge)/(right_edge - right_eye);
    
    cout.precision(3);
    cout << "ratio:" << fixed << ratio << endl;
    
    //Conditional statements on blurriness and straightness values, return -1 to bash script if met
    if (blurriness > 0.0003) {
        cout << "im sorry this is just too blurry" << endl;
        return -1;
    }
    
    else {
        cout << "zomg, this pic is so crisp!" << endl;
    }

    
    if (ratio > 2 || ratio < 0.5){
        cout << "im sorry this is not straight on" << endl;
        return -1;
    }
    
    else {
        cout << "zomg, straight as a doornail!" << endl;
    }
    
    //convert Mat to float data type
    img1.convertTo(img1, CV_32F);
    img1Warped.convertTo(img1Warped, CV_32F);
    
    
    // Find convex hull
    vector<Point2f> hull1;
    vector<Point2f> hull2;
    vector<int> hullIndex;
    
    convexHull(points2, hullIndex, false, false);
    
    for(int i = 0; i < hullIndex.size(); i++)
    {
        hull1.push_back(points1[hullIndex[i]]);
        hull2.push_back(points2[hullIndex[i]]);
    }

    
    // Find delaunay triangulation for points on the convex hull
    vector< vector<int> > dt;
	Rect rect(0, 0, img1Warped.cols, img1Warped.rows);
	calculateDelaunayTriangles(rect, hull2, dt);
	

	// Apply affine transformation to Delaunay triangles
	for(size_t i = 0; i < dt.size(); i++)
    {
        vector<Point2f> t1, t2;
        // Get points for img1, img2 corresponding to the triangles
		for(size_t j = 0; j < 3; j++)
        {
			t1.push_back(hull1[dt[i][j]]);
			t2.push_back(hull2[dt[i][j]]);
		}
        
        warpTriangle(img1, img1Warped, t1, t2);

	}

    
    // Calculate mask
    vector<Point> hull8U;
    for(int i = 0; i < hull2.size(); i++)
    {
        Point pt(hull2[i].x, hull2[i].y);
        hull8U.push_back(pt);
    }
    Mat mask = Mat::zeros(img2.rows, img2.cols, img2.depth());
    fillConvexPoly(mask,&hull8U[0], hull8U.size(), Scalar(255,255,255));


    // Clone seamlessly.
    Rect r = boundingRect(hull2);
    Point center = (r.tl() + r.br()) / 2;
    
    Mat output;
    img1Warped.convertTo(img1Warped, CV_8UC3);
	seamlessClone(img1Warped,img2, mask, center, output, NORMAL_CLONE);
    
    imwrite(string(argv[3]) + "/out" + string(argv[4]) + ".png", output);
    
    return 0;
    
}
