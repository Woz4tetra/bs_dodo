import logging
import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

client = roslibpy.Ros(host="192.168.50.169", port=9090)

publisher = roslibpy.Topic(client, "/dodobot/tilter_cmd", "db_parsing/DodobotTilter")
publisher.advertise()

def enable_motors():
    service = roslibpy.Service(client, "/dodobot/set_state", "db_parsing/DodobotSetState")
    set_state_request = roslibpy.ServiceRequest({"reporting": True, "active": True})
    result = service.call(set_state_request)
    log.info(f"Set motor request response: {result}")

    client.call_later(1.0, send_notification)


def send_notification() -> None:
    log.info("Sending notification")
    msg = roslibpy.Message({ "header": {"seq": 0, "stamp": 0, "frame_id": ""},"position": 0, "command": 0})
    publisher.publish(msg)
    log.info("Notification sent")

    # client.call_later(2.0, send_notification)

client.on_ready(enable_motors)
client.run_forever()
