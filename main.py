import cv2  # Import the OpenCV library 
from ultralytics import YOLO  # Import the YOLO class from the Ultralytics library
import numpy as np  # Import NumPy for numerical operationse

# Function to set up the camera
def CameraSetup():
    cap = cv2.VideoCapture(0)  # Open the default camera (0 = built-in webcam)

    # Set video format to MJPG (better performance than default)
    cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M','J','P','G'))

    # Set the width and height of the video frame
    cap.set(3, 960)  # Width
    cap.set(4, 640)  # Height

    print("Camera setup complete.")
    return cap

# Function to capture a frame from the camera
def GetImage(cap):
    ret, image = cap.read()  # 'ret' is a success flag; 'image' is the captured frame
    return image

# Function to display an image in a window
def ShowImage(img):
    cv2.imshow('image', img)  # Show the image in a new window

# Function to load a YOLOv11 model
def LoadModel(model_path="yolo11s.pt"):
    model = YOLO(model_path)  # Load the model from the given path
    print(f"Model successfully loaded from {model_path}")
    return model

# Function to perform object detection on a given source
def GetResult(model, source):
    results = model.predict(source)  # Predict on the input (image, video, etc.)
    result = results[0]  # Take the first result (usually only one for static image)
    return result

# Function to extract and print bounding box data
def ObtainData(result):
    for box in result.boxes:
        cls = int(box.cls[0])  # Get class index
        x, y, w, h = box.xywh[0]  # Get box center x, y, width, height
        x, y, w, h = int(x), int(y), int(w), int(h)  # Convert to integers
        conf = float(box.conf[0])  # Get confidence score
        print(f"Box: x={x}, y={y}, w={w}, h={h}, Confidence: {conf:.2f}, Class: {cls}")
        ###############################################################################
        if cls == 77:
            return (x, y, w, h)  # Return box if class is 77 (cell phone)
    return None  # Return None if no box of class 77 is found

def px_to_cm_x_offset(offset_px, distance_cm, frame_width=960, fov_deg=45):
    # Každý pixel představuje určitý úhel
    deg_per_px = fov_deg / frame_width
    angle_rad = np.radians(offset_px * deg_per_px)

    # Přepočet offsetu na cm pomocí tangensu a hloubky
    cm_offset = np.tan(angle_rad) * distance_cm
    return cm_offset

model = LoadModel()  # Load the YOLOv11 model
# Example usage
cap = CameraSetup()       # Initialize the camera

while True:
    image = GetImage(cap)        # Capture a frame
    # Run detection on the input image
    result = GetResult(model, image)
    x, y, w, h = ObtainData(result)  # Extract bounding box data
    relative_x = x - 480  # Calculate relative x position from center
    relative_y_bottom = 690 - (y + round(h/2)) # Calculate relative y position from bottom center
    print(f"Relative Position: x={relative_x}, y_bottom={relative_y_bottom}")  # Print relative position
    y_cm = 0.07895052 * np.e**(0.02147171 * relative_y_bottom) + 35.468015

    x_cm = px_to_cm_x_offset(relative_x, y_cm)
    print(f"Calculated x position in cm: {x_cm}")
    print(f"Calculated y position in cm: {y_cm}")
    

    cv2.circle(image, (x, y + round(h/2)), 5, (255, 0, 255), -1)  # Draw center point
    cv2.rectangle(image, (x - round(w/2), y - round(h/2)), (x + round(w/2), y + round(h/2)), (0, 255, 0), 2)  # Draw bounding box
    cv2.line(image, (x, 0), (x, 640), (0, 0, 255), 1)  # Draw vertical line
    cv2.line(image, (0, y + round(h/2)), (960, y + round(h/2)), (0, 0, 255), 1)  # Draw horizontal line
    cv2.line(image, (480, 0), (480, 640), (255, 0, 0), 1)  # Draw center vertical line
    cv2.line(image, (0, 320), (960, 320), (255, 0, 0), 1)  # Draw center horizontal line


    # Print bounding box data
    ShowImage(image)# Display the frame
    if cv2.waitKey(1000) & 0xFF == ord('q'):  # Exit loop if 'q' is pressed
        break
cap.release()  # Release the camera
cv2.destroyAllWindows()  # Close all OpenCV windows