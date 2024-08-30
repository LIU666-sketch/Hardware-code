import cv2
import numpy as np
import serial
import time
import pytesseract


# 初始化串口通信
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit(1)

# 创建一个黑色的500x500图像，并在中心绘制数字9
default_image = np.zeros((500, 500, 3), dtype=np.uint8)
font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(default_image, '9', (200, 300), font, 10, (255, 255, 255), 20, cv2.LINE_AA)
cv2.imwrite('default.jpg', default_image)

# 默认图像路径
DEFAULT_IMAGE_PATH = 'default.jpg'
CAPTURE_IMAGE_PATH = 'capture.jpg'  # 保存摄像头捕获图像的路径

# 图像识别函数
def recognize_image(image_path):
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # 使用Tesseract OCR识别图像中的文本
    text = pytesseract.image_to_string(gray, config='--psm 6')
    return text.strip()

# 发送串口指令
def send_command(command):
    try:
        ser.write(command)
        time.sleep(0.1)
    except serial.SerialException as e:
        print(f"Error sending command: {e}")

# 接收串口指令
def receive_command():
    try:
        return ser.read_all()
    except serial.SerialException as e:
        print(f"Error receiving command: {e}")
        return b''

# 图像展示函数
def display_image(image_path):
    image = cv2.imread(image_path)
    cv2.imshow('Image', image)
    cv2.waitKey(1)  # 显示1毫秒

# 从摄像头获取图像并保存
def get_and_save_camera_image():
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()
    cap.release()
    if not ret:
        print("Error: Could not capture image from camera")
        frame = cv2.imread(DEFAULT_IMAGE_PATH)
    cv2.imwrite(CAPTURE_IMAGE_PATH, frame)
    return CAPTURE_IMAGE_PATH

# 模式1逻辑
def mode1():
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if 'A' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break
            
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   
    
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x07')
            print('Sent command: 7')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '7' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x06')
            print('Sent command: 6')
            break   


# 模式2逻辑
def mode2():
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if 'B' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break
            
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   
    
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x07')
            print('Sent command: 7')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '7' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x07')
            print('Sent command: 7')
            break   


# 模式3逻辑
def mode3():
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if 'C' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break
            
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   
    
    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x00')
            print('Sent command: 0')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '0' in recognized_text:
            send_command(b'\x07')
            print('Sent command: 7')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '7' in recognized_text:
            send_command(b'\x01')
            print('Sent command: 1')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '1' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

    while True:
        image = get_and_save_camera_image()
        recognized_text = recognize_image(image)
        display_image(image)
        if '2' in recognized_text:
            send_command(b'\x02')
            print('Sent command: 2')
            break   

# 主程序
def main():
    mode=int(input("请输入模式："))
    # 示例模式，可以通过其他逻辑切换模式
    if mode == 1:
        mode1()
    elif mode == 2:
        mode2()
    elif mode == 3:
        mode3()

if __name__ == "__main__":
    main()
