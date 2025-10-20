import base64
import logging
import time

import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

client = roslibpy.Ros(host="192.168.50.169", port=9090)

publisher = roslibpy.Topic(client, "/dodobot/notify", "db_parsing/DodobotNotify")
publisher.advertise()


def send_notification(message: str, duration: float) -> None:
    log.info(f"Sending notification: {message} for {duration} seconds")
    notification_msg = roslibpy.Message({"message": message, "level": 0, "timeout": int(duration * 1000)})
    publisher.publish(notification_msg)
    log.info("Notification sent")

    client.call_later(2.0, lambda: send_notification("hi", 1.0))

client.on_ready(lambda: send_notification("hi", 1.0))
client.run_forever()
