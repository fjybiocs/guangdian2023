import cv2
import color_detect
import line_detect
import line_processor

line_thickness = 0

img = cv2.imread("image.png")

bottom_left, top_right = color_detect.get_map_edge(img)

x1, y1 = bottom_left
x2, y2 = top_right
left, top = min(x1, x2) + line_thickness, min(y1, y2) + line_thickness
right, bottom = max(x1, x2) - line_thickness, max(y1, y2) - line_thickness

# 裁剪图像
img = img[top:bottom, left:right]

lines = line_detect.get_line(img)

# 显示原图和裁剪后的图像
cv2.imshow("Original Image", img)
cv2.waitKey(0)

height, width, channels = img.shape
line_processor.line_process(lines, width, height, img)
