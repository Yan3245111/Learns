* 先给要启动的脚本权限
chmod +x path

* 创建服务文件
sudo nano /etc/systemd/system/servo_server.service  更改为你的服务名字.service

* 添加以下内容

[Unit]
Description=Servo Server
After=network.target

[Service]
Type=simple
User=root
WorkingDirectory=/home/surgicalai/servo_server  更换为脚本路径
ExecStart=/bin/bash /home/surgicalai/servo_server/restart.sh  更换为执行脚本 如果是python 更改为python 启动路径
Restart=always
RestartSec=5  # 崩溃后5s再启动

[Install]
WantedBy=multi-user.target

* 设置开机自启
sudo systemctl enable servo_server.service

* 启动服务
sudo systemctl start servo_server.service

* 查看状态
sudo systemctl status servo_server.service

* 停止自启动
sudo systemctl disable servo_server.service