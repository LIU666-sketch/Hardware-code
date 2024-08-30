#!/usr/bin/env python  
# -*- coding:utf-8 -*- 
""" 
@author: h2078 
@contact: h207835@163.com
@file: detect.py
@time: 2024/7/22 17:16
@project: NumberOCR
"""
import os.path
import cv2
import numpy as np
import time
import serial
import pytesseract

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"
# 默认图像路径
DATA_DIR = "./pics"  # 保存摄像头捕获图像的路径
IMG_PATH = os.path.join(DATA_DIR, "capture.jpg")

mode = 0
person_id = {
    1: "20221071298",
    2: "20221071469",
    3: "20221082016"
}
number_set = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
char_set = {'A', 'B', 'C'}

# 初始化串口通信
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit(1)


def send(command):
    try:
        ser.write(command)
        time.sleep(0.1)
    except serial.SerialException as e:
        print(f"Error sending command: {e}")


def get_img():
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()
    cv2.imwrite(IMG_PATH, frame)
    cap.release()
    return IMG_PATH

def display_image(img_path):
    img = cv2.imread(img_path)
    cv2.imshow('img', img)
    cv2.waitKey(1)  # 显示10毫秒


def recognize(img_path):
    # 图片预处理
    img = cv2.imread(img_path)
    img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)  # 灰度转换
    img = cv2.GaussianBlur(img, (5, 5), 0)  # 高斯滤波--去噪点
    img = cv2.Canny(img, 75, 200)  # 边缘检测
    # Tesseract OCR识别文本
    text = pytesseract.image_to_string(img, config='--psm 6')
    return text


def detect():
    text_char = set()
    while True:
        img = get_img()
        text = recognize(img)
        text_char = text_char | (set(text) & char_set)
        display_image(img)
        print(text_char)
        if "A" in text_char:
            mode = 1
            send(b'\x02')
            break
        elif "B" in text_char:
            mode = 2
            send(b'\x02')
            break
        elif "C" in text_char:
            mode = 3
            send(b'\x02')
            break
        else:
            mode = 0
    print("mode %d" % mode)
    check_id = list(person_id[mode])
    pos = 0
    while True:
        check_number = check_id[pos]
        print("check number: %c" % check_number)
        text_number = set()
        while True:
            img = get_img()
            text = recognize(img)
            text_number = text_number | (set(text) & number_set)
            display_image(img)
            print(text_number)
            if check_number in text_number:
                pos += 1
                print("pos: %d" % pos)
                if pos < 11:
                    next_number = check_id[pos]
                    send(bytes([int(next_number)]))
                break
        if pos == 11:
            print("check done")
            break


if __name__ == "__main__":
    detect()
