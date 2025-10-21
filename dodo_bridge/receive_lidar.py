import logging
import time

import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

client = roslibpy.Ros(host="192.168.50.169", port=9090)

def receive_scan(message):
    try:
        header = message.get('header', {})
        seq = header.get('seq', 'unknown')
        timestamp = header.get('stamp', {}).get('secs', 0)
        delay = time.time() - timestamp if timestamp else 0
        log.info(f"Received image seq={seq}. Delay: {delay:.2f} seconds")
    except Exception as e:
        log.error(f"Error processing image message: {e}")
        import traceback
        traceback.print_exc()

subscriber = roslibpy.Topic(client, "/laser/scan", "sensor_msgs/LaserScan")
subscriber.subscribe(receive_scan)

client.run_forever()
