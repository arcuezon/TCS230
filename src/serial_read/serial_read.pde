import processing.serial.*;

Serial myPort;
int red = 0;
int green = 0;
int blue = 0;

void setup() 
{
  size(800, 800);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 57600);
  myPort.bufferUntil('\n');
}

void draw()
{
  while ( myPort.available() > 3) {
    if(myPort.read() == 'H'){
      red = myPort.read();         
      green = myPort.read();
      blue = myPort.read();
    }
  }
  
  print("Red: ");
  print(red);
  print(" Green: ");
  print(green);
  print(" Blue: ");
  println(blue);
  
  fill(red, green, blue);

  rect(200, 200, 400, 400);
  
  delay(1000);
}
