
int rectX, rectY;      // Position of square button
int rectSize = 120;     // Diameter of rect
color rectColor, baseOP;
color rectHighlight;
color currentOP;

int textColor;

boolean rectOver = false;


void setup() {
  size(680, 480);
  rectColor = color(0);
  rectHighlight = color(51);
  
  baseOP = 255;
  currentOP = baseOP;
  
  textColor = 255;
  
  rectX = width/2;
  rectY = height/3*2;
  rectMode(CENTER);
}

void draw() {
  update(mouseX, mouseY);
  background(0);
  
  if(currentOP>=0){
  String c = "You're____";
  fill(textColor,255);
  textSize(34);
  textAlign(CENTER); 
  text(c,width/2,height/3);
 }
  
  fill(0,currentOP);
  rect(width/2,height/2,width,height);
  
  if (rectOver) {
    fill(rectHighlight, currentOP);
  } else {
    fill(rectColor, currentOP);
  }
  stroke(255,currentOP);
  rect(rectX, rectY, rectSize, rectSize);
    
  String a = "FIND THE ANWSER...";
  fill(textColor,currentOP);
  textSize(34);
  textAlign(CENTER); 
  text(a,width/2,height/3);
  
  String b = "ENTER!";
  fill(textColor,currentOP);
  textSize(24);
  textAlign(CENTER); 
  text(b,width/2,2.05*height/3);
  

}

void update(int x, int y) {
  if ( overRect(rectX, rectY, rectSize, rectSize) ) {
    rectOver = true;
 
  } else {
    rectOver = false;
  }
  
}

void mousePressed() {
  if (rectOver) {
    currentOP = 0;
  }
}



boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x-width/2 && mouseX <= x+width/2 && 
      mouseY >= y-height/2 && mouseY <= y+height/2) {
    return true;
  } else {
    return false;
  }
}
