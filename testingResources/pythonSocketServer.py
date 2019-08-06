#! /usr/bin/python3

import asyncio
import websockets
import time

async def hello(websocket, path):
    name = await websocket.recv()
    print(f"< {name}")
    greeting = f"Hello {name}!"
    await websocket.send(greeting)
    print(f"> {greeting}")
    time.sleep(10)

start_server = websockets.serve(hello, "localhost", 5001)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
