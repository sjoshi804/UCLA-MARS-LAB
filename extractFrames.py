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
	framesToSkip = 0 #change this to change granularity of extraction
	skipCounter = framesToSkip

	while success: 

		# vidObj object calls read 
		# function extract frames 
		success, image = vidObj.read() 
		
		#See if this is a relevant frame or one to be skipped - modify granularity of extraction
		if skipCounter == 0:
			# Saves the frames with frame-count 
			cv2.imwrite("frame%d.jpg" % count, image)
			skipCounter = framesToSkip
		else:
			skipCounter -= 1

		count += 1

# Driver Code 
if __name__ == '__main__': 

	# Calling the function 
	FrameCapture("../stockFaceFootage.mp4") 
