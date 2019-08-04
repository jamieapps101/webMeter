class websocketControl {
  constructor()
  {
    self.ip = "";
    self.connected = 0;
  }

  setIP(ip)
  {
    self.ip = ip;
  }

  connect()
  {
    // var IPre = new RegExp('[\d\d]');
    // var portre = new RegExp('(:(\d){0,})(?!:)');
    //var ipComp = /\d\d/g.match(self.ip);
    var ipComp = self.ip.match(/\d{2}/g);

    console.log(ipComp);

    if(ipComp.length == 4 && portComp.length == 1)
    {
      self.socket = new webSocket(self.ip);
      self.socket.addEventListener('open', self.onConnect(event));
      self.socket.addEventListener('close', self.onDisconnect(event));
      self.socket.addEventListener('message', self.onMessage(event));
      self.socket.addEventListener('error', self.onError(event));
    }
    else
    {
      console.log("Error in ip: " + self.ip);
    }
  }

  onConnect(event)
  {
    console.log("Websocket Connected");
    self.connected = 1;
  }

  onDisconnect(event)
  {
    console.log("Websocket Disconnected");
    self.connected = 0;
  }

  onMessage(event)
  {
    console.log("message from websocket:")
    console.log(event);
  }

  onError(event)
  {
    console.log("websocket error, closing")
    self.connected = 0;
  }

  sendData(data)
  {
    self.socket.send(data);
  }

  disconnect()
  {
    self.socket.close();
    self.connected = 0;
  }
}
