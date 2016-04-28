import cv2
import datetime
import time
import sys

cascPath = "haarcascade_frontalface_alt.xml"
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)

is_there_a_face = 0

while is_there_a_face == 0:
    # Capture frame-by-frame
    #time.sleep(1)
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.CASCADE_SCALE_IMAGE
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        #date = datetime.datetime.now().strftime('%m_%d_%y_%h_%m_%s_')
        cv2.imwrite('test.jpg',frame)
        #time.sleep(0.25)
        is_there_a_face = 1

    # Display the resulting frame
    cv2.imshow('Video', frame)

    #if cv2.waitKey(1) & 0xFF == ord('q'):
    #    break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
