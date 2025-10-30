\## Create a systemd service file

sudo nano /etc/systemd/system/hiddenserver.service





Paste this in:

```

\[Unit]

Description=Hidden Python HTTP Server

After=network.target



\[Service]

Type=simple

ExecStart=/usr/bin/python3 -m http.server 6969 --directory /home/youruser/myserver

WorkingDirectory=/home/youruser/myserver

Restart=always

StandardOutput=null

StandardError=null

User=youruser



\[Install]

WantedBy=multi-user.target

```



Replace youruser and folder path with valid values.



\## Enable and start it

sudo systemctl enable hiddenserver

sudo systemctl start hiddenserver



\## 🔍 Check if it’s running

systemctl status hiddenserver



\## ✅ Stop it if you need

`sudo systemctl stop hiddenserver`



Access from other PCs on LAN



Find server IP:



`ip a | grep inet`





Then open in browser:



`http://<SERVER-IP>:6969/`

