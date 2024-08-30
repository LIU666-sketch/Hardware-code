from PIL import Image
# 打开图片并调整为指定大小
img = Image.open('D:\Desktop\dl\微信图片_20240718223318.jpg').resize((120, 120))
# 将图片转换为RGB格式
img = img.convert('RGB')
# 获取图片数据
pixel_data = list(img.getdata())
# 将图片数据转换为适合LCD的格式
pic = []
for pixel in pixel_data:
    r, g, b = pixel
# 假设LCD使用16位颜色格式（5位红色，6位绿色，5位蓝色）
    rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    pic.append(rgb565 >> 8)  # 高8位
    pic.append(rgb565 & 0xFF)  # 低8位
#将数据保存为C数组格式
with open('pic_data.h', 'w') as f:
    f.write('const unsigned char pic[] = {\n')
    for i in range(0, len(pic), 12):  # 每行显示12个数据
        f.write('    ' + ', '.join(f'0x{byte:02X}' for byte in pic[i:i+12]) + ',\n')
    f.write('};\n')