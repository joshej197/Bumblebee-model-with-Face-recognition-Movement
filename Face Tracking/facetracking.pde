import gab.opencv.*;
import processing.video.*;
import java.awt.*;
import processing.serial.*;
import processing.sound.*;
  
  SoundFile file;
  //replace the sample.mp3 with your audio file name here
  String audioName = "audio.wav";
  String path;
Serial myPort;


Capture video;
OpenCV opencv;

long prevtime=0;
long interval = 15;

void setup() {
  size(1280, 960);
  
  String portName = Serial.list()[2];
  String[] cameras = Capture.list();
  myPort = new Serial(this, portName, 9600);
  video = new Capture(this,320,240, cameras[11]);
  opencv = new OpenCV(this, 320, 240);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);  
    path = sketchPath(audioName);
    file = new SoundFile(this, path);
  video.start();
}

void draw() {
  long curtime=second();
  scale(4);
  opencv.loadImage(video);

  image(video, 0, 0 );

  noFill();
  stroke(0, 255, 0);
  strokeWeight(3);
  Rectangle[] faces = opencv.detect();
  println(faces.length);
  if(abs(curtime-prevtime) >=interval){
 
    if(faces.length>0)
  { myPort.write("n"); 
    myPort.write("m");
     prevtime=curtime;
      file.play();
     file.rate(0.5);
   }
 
 }
  for (int i = 0; i < faces.length; i++) {
    println(faces[0].x + "," + faces[0].y);
    rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height);  
    if(faces[0].x > 180)
   {
    myPort.write("d"); 
   }
    if(faces[0].x < 140)
   {
    myPort.write("a"); 
   }
  }
}
void captureEvent(Capture c) {
  c.read();
}
