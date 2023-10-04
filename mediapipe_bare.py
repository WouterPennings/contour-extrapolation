import sys
import time
import math

import cv2 as cv
import mediapipe as mp

def estimate_pose(cam_or_vid: str):
	mp_pose = mp.solutions.pose
	pose = mp_pose.Pose(model_complexity=1)

	cap = cv.VideoCapture(0, cv.CAP_DSHOW) if cam_or_vid == "--webcam" else cv.VideoCapture(cam_or_vid)
	pose = mp_pose.Pose(
		min_detection_confidence=0.5, min_tracking_confidence=0.5, model_complexity=0
	)
	
	start_time = time.time()
	
	for i in range(0, 1000):
		# Get frame from vid or webcam
		_, frame = cap.read()

		# To improve performance, optionally mark the image as not writeable to
		# pass by reference.
		frame.flags.writeable = False
		frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
		results = pose.process(frame)

		# Quit if 'q' is pressed
		if cv.waitKey(1) & 0xFF == ord("q"):
			break
			
	end_time = time.time()
	print(end_time - start_time)
        
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please provide either '--webcam', or a filename of a video")
        exit()
	
    estimate_pose(sys.argv[-1])
