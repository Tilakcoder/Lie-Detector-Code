double thresh = 3;
double answer;
double mA;
double mAMax = 0;
double mAMin = 1000;
bool training = true;
bool up = false;

int iit = 0;

bool result = true;

bool start = millis();


bool high = true;
double Prev_minis=0;
double minis = 0;

class AVG{
  public:
    int n = 100;
    double vs[100];
    double avg_count=0;
    double average=0;
    double avg_deno;
    bool reach = false;
    double minV = 1000, maxV = 0;
    double ans;

    double calc(double v){
      vs[(int)avg_count] = v;
      
      avg_count += 1;
      
      avg_deno = avg_count;
      if(reach){
        average -= vs[(int)avg_count];
        vs[(int)avg_count] = v;
        avg_deno = n;
      }

      average += v;
      avg_count += 1;
      
      if(avg_count == n){
        reach = true;
        avg_count = 0;
        maxV = 0;
        minV = 1000;
        
      }
      ans = average/avg_deno;

      if(ans>maxV){
        maxV = ans;
      }
      if(ans<minV){
        minV=ans;
      }
      return ans;
    }

    double last(){
      return vs[(int)avg_count];
    }
  
};

AVG pr;
AVG avg;
AVG rate;

void setup() {
//  avg.n = 50;
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
//  minis = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  double o = analogRead(A0);
  
  answer = pr.calc(o);
  mA = avg.calc(pr.maxV)+thresh;

  if(mA>mAMax && training){
    mAMax = mA;
  }
  if(mA<mAMin && training){
    mAMin = mA;
  }

  if(millis() - start > 10000 && training && !up){
    mAMax = 0;
    mAMin = 1000;
    up = true;
  }

  if(millis()-start > 20000){
    training = false;
  }

//  Serial.print(mAMax+0.08);
//  Serial.print(" ");
//  Serial.print(mA);
//  Serial.print(" ");
//  Serial.print(mAMin);
//  Serial.print(" ");
//  Serial.println("");

  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println("");

  if(mA>mAMax+0.08 || mA<mAMin){
    result = false;
    digitalWrite(13, HIGH);
  }

  if(iit%100 == 0){
    iit = 0;
    result = true;
    digitalWrite(13, LOW);
  }
  
  delay(20);
  iit += 1;
}
