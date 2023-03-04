import os
from PIL import Image

# 指定目录路径
directory = r'C:\Users\41132\Desktop\EPSG_4326_16'
width = 256
height = 256
xCount = 0
yCount = 0

picxy = {}
picPathDic = {}
# 遍历目录中的所有文件
for root, dirs, files in os.walk(directory):
    for file in files:
        # 打印文件名称和路径
        # print(os.path.join(root, file))
        x, y = file.split('_')
        if False == (x in picxy):
            picxy[x] = set()
        ySet = picxy[x]
        ySet.add(y)
        picPathDic[file] = os.path.join(root, file)

sorted_keys = sorted(picxy.keys())
print("xCount的数量")
print(len(sorted_keys))
xCount = len(sorted_keys)

for x in sorted_keys:
    ySet = picxy[x]
    ySet = sorted(ySet)
    print("yCount的数量")
    print(len(ySet))
    yCount = len(ySet)
    break

IMG_OUT = Image.new("RGB", (xCount*width, yCount*height))
indexX = 0
for x in sorted_keys:
    indexY = 0
    ySet = picxy[x]
    ySet = sorted(ySet, reverse=True)
    for y in ySet:
        img_path = picPathDic[x+"_"+y]
        with Image.open(img_path) as img:
            IMG_OUT.paste(img, (indexX*width, indexY*height))
        indexY = indexY+1
    indexX = indexX+1

IMG_OUT.save(os.path.join(directory, "imageMerge.png"))
