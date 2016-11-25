from pylab import *
import sys, cv2

filename = "Pcb.png"
#filename = "red box pcb.jpg"
# http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html
img = cv2.imread(filename,0);
cimg = cv2.cvtColor(img,cv2.COLOR_GRAY2BGR);
H, W = img.shape
print H, W
# 63 su 71
# circles = cv2.HoughCircles(img,cv2.cv.CV_HOUGH_GRADIENT,2,10,param1=100,param2=30,minRadius=4,maxRadius=13);
# 66 su 71
#circles = cv2.HoughCircles(img,cv2.cv.CV_HOUGH_GRADIENT,2,10,param1=100,param2=30,minRadius=4,maxRadius=14);
circles = cv2.HoughCircles(img,cv2.cv.CV_HOUGH_GRADIENT,2,10,param1=100,param2=30,minRadius=4,maxRadius=14);
circles = np.uint16(np.around(circles));
for i in circles[0,:]:
    #cv2.circle(cimg,(i[0],i[1]),i[2],(0,255,0),1);
    cv2.circle(cimg,(i[0],i[1]),2,(0,0,255),3);
    print i[0], i[1]
cv2.imwrite('1-%s'%(filename),cimg)
print "%d circles found."%(len(circles[0]));