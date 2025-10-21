import logging
import time

import roslibpy

# Configure logging
fmt = "%(asctime)s %(levelname)8s: %(message)s"
logging.basicConfig(format=fmt, level=logging.INFO)
log = logging.getLogger(__name__)

client = roslibpy.Ros(host="192.168.50.169", port=9090)

source = "client"
last_send_time = None

def receive_ping(message):
    global last_send_time
    receive_time = time.perf_counter()
    
    header = message.get('header', {})
    seq = header.get('seq', 0)
    stamp = header.get('stamp', 0)
    sec = stamp.get('secs', 0)
    nsec = stamp.get('nsecs', 0)
    timestamp = sec + nsec * 1e-9
    
    # Calculate round-trip delay
    delay = receive_time - timestamp if timestamp else 0
    
    # Calculate time between consecutive pings (should be ~delay*2 for back-to-back)
    interval = receive_time - last_send_time if last_send_time else 0
    
    # Log with extra info for spikes
    if delay > 0.05:  # Flag delays > 50ms
        log.warning(f"SPIKE! seq={seq}. Delay: {delay:.4f}s, Interval: {interval:.4f}s")
    else:
        log.info(f"Received ping seq={seq}. Delay: {delay:.4f}s, Interval: {interval:.4f}s")
    
    send_ping()  # Send next ping immediately


def send_ping() -> None:
    global last_send_time
    timestamp = time.perf_counter()
    last_send_time = timestamp
    sec = int(timestamp)
    nsec = int((timestamp - sec) * 1e9)
    ping_msg = roslibpy.Message({"header": {"stamp": {"secs": sec, "nsecs": nsec}}, "source": source})
    publisher.publish(ping_msg)

publisher = roslibpy.Topic(client, "/dodobot/ping_in", "db_parsing/Ping")
publisher.advertise()

subscriber = roslibpy.Topic(client, "/dodobot/ping_out", "db_parsing/Ping")
subscriber.subscribe(receive_ping)


client.on_ready(lambda: send_ping())
client.run_forever()
