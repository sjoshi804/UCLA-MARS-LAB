# Program To Read video 
# and Extract Frames 
import cv2 

# Function to extract frames 
def FrameCapture(path): 
	
	# Path to video file 
	vidObj = cv2.VideoCapture(path) 

	# Used as counter variable 
	count = 0

	# checks whether frames were extracted 
	success = 1
	framesToSkip = 0 #change this to change granularity of extraction - 0 highest granularity
	skipCounter = framesToSkip

	while success: 

		# vidObj object calls read 
		# function extract frames 
		success, image = vidObj.read()
		greyscaleImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
		croppedImage = greyscaleImage[0:720, 400:880]
		finalImage = cv2.resize(croppedImage, None, fx = 1/3, fy = 1/3, interpolation=cv2.INTER_AREA)
		#See if this is a relevant frame or one to be skipped - modify granularity of extraction
		if skipCounter == 0:
		# Saves the frames with frame-count 
			cv2.imwrite("sampleFrames/frame%d.pgm" % count, finalImage)
			skipCounter = framesToSkip
		else:
			skipCounter -= 1

		count += 1

# Driver Code 
if __name__ == '__main__': 

	# Calling the function 
	FrameCapture("../stockFaceFootage.mp4") 
