import numpy as np
import cv2

cap = cv2.VideoCapture('../stockFaceFootage.mp4')
count = 0
while (cap.isOpened()):
	ret, frame = cap.read()
	if not ret:
		break
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	crop = gray[0:720, 160:1120]
	final = cv2.resize(crop, (320, 240), interpolation=cv2.INTER_AREA)
	#cv2.imshow('frame',final)
	name = 'frame' + str(count) + '.pgm'
	print("Writing " + name)
	cv2.imwrite(name, final)
	#cv2.imwrite("sampleFrames/frame%d.pgm" % count, final)
	count += 1
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()