# 基于NodeMCU播放的BadApple

## 依赖

- Arduino IDE
- Arduino sketch data upload插件
- 一块NodeMCU
- 一个OLED显示屏

## 使用步骤

- Arduino IDE配置Flash文件系统为3M，烧录程序
- 使用Arduino sketch data upload 上传视频文件`video.dat`
- 接线，复位播放视频

## TODO

- 由于Flash大小限制，当前视频只有2000帧