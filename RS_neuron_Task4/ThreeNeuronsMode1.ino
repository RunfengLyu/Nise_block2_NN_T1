#define NUMBER_RS_NEURONS 3

//three neuron system, please comment different part to run different mode

/******************************************************/ 
//struct RSneuron 
/******************************************************/ 
struct RSneuron { 
  float x = 0;       // membrane potential
  float x_old = 0;
  float y = 0;       // output response of neuron
  float tau = 1;     // time const.
  int s = 50;     // impulse rate
  float b;       // adaptation coefficient b = 0, 2.5, inf
  float x_prime = 0; // degree of adaptation
  float x_prime_old = 0;
  float y_old = 0;
  float T;       // time constant for adaptation T = 2.5, 12, inf
  float theta = 0;   // threshold
} rs_neuron[NUMBER_RS_NEURONS];

float time_step = 0.1;


void setup() {
  
  Serial.begin(115200);

  rs_neuron[0].b = 2.5;
  rs_neuron[0].T = 12;

  rs_neuron[1].b = 2.5;
  rs_neuron[1].T = 12;

  rs_neuron[2].b = 2.5;
  rs_neuron[2].T = 12;

 
  
}

/******************************************************/ 

int i = 0;
int j = 0;
float net_input = 0;
float a[3] = {2.5,0,0};


void loop()
{

  //mode 1: neurons are double-sided connected, i.e a1 = a2 =2.5
  
  for(i = 0; i < NUMBER_RS_NEURONS; i ++){

    for(j = 0; j<NUMBER_RS_NEURONS; j ++){
      if(i!=j){

      net_input = net_input + 2.5 * rs_neuron[j].y;
      }
      
      }

    
    rs_neuron[i].x = (1 - time_step)*rs_neuron[i].x_old + time_step * (-net_input + 1.0  - (rs_neuron[i].b * rs_neuron[i].x_prime_old));
    
    rs_neuron[i].x_prime = (1 - time_step/rs_neuron[i].T)*rs_neuron[i].x_prime_old + time_step * rs_neuron[i].y / rs_neuron[i].T;
    
    rs_neuron[i].y = max(0.0f, rs_neuron[i].x_old - rs_neuron[i].theta);
    

    rs_neuron[i].x_old = rs_neuron[i].x;
    
    rs_neuron[i].x_prime_old = rs_neuron[i].x_prime;
    net_input = 0;
  }


  Serial.print("Neuron0:"); Serial.print(rs_neuron[0].y); Serial.print("  ");
  Serial.print("Neuron1:"); Serial.print(rs_neuron[1].y); Serial.print("  ");
  Serial.print("Neuron2:"); Serial.print(rs_neuron[2].y); Serial.println("  ");
  //Serial.println(float(!(count%2)));
  //Serial.print("Neuron2:"); Serial.print(rs_neuron[2].y); Serial.println("  ");

  delay(100);
  
    
}

   
  
