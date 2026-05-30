#include<iostream>
using namespace std;
#include<cmath>

float True_air_speed(float IAS , float Altitude){

float TAR;

TAR = IAS * (1 + (0.02 * (Altitude / 1000)));

return TAR ;
}

float Drift_angle(float Wind_speed , float Wind_direction , float True_air_speed , float Track){

    float angle;
   const double pi =  3.141592653589793;
    angle = Wind_direction - Track;

     float c_angle = angle * (pi /180);

   float value = (Wind_speed / True_air_speed) * sin(c_angle);

if (value > 1) value = 1;
if (value < -1) value = -1;

float Drift = asin(value);
Drift = Drift * (180 / pi);
if (abs(Drift) < 0.0001)
    Drift = 0;
    return Drift;
}




float True_Heading(float Track, float Drift_angle) {

    float TH = Track - Drift_angle;
    if (TH < 0) TH += 360;
    if (TH >= 360) TH -= 360;

    return TH;
}

 
float Ground_speed(float TAS, float Drift, float Wind_speed, float Wind_direction, float Track) {
    const double pi = 3.141592653589793;

    
    float wind_blowing_to = Wind_direction + 180;
    if (wind_blowing_to >= 360) wind_blowing_to -= 360;

   
    float angle_diff = wind_blowing_to - Track;

  
    double angle_rad = angle_diff * (pi / 180.0);
    double drift_rad = Drift * (pi / 180.0);
    float Ground_speed = sqrt(pow(TAS, 2) + pow(Wind_speed, 2) + (2 * TAS * Wind_speed * cos(angle_rad)));
    return Ground_speed;
}




float Time(float distance , float Ground_speed){

    float Time = distance / Ground_speed;

    return Time;
}

float fuel_consumption(float Time , float fuel_flow_rate){

    float feul_consumed = Time * fuel_flow_rate;

    return feul_consumed;
}

int main(){
     
    cout<<"Hello Captain Please enter the following information to calculate your flight parameters: "<<endl;
    cout<<"Enter your name: ";
    string Name;
    getline(cin , Name);
    cout<<"Enter the indicated air speed (IAS): ";
    float IAS ;
    cin>>IAS;



    cout<<"Enter the altitude (in feet): ";
    float altitude;
    cin>>altitude;



    cout<<"Enter the Track (in degrees): ";
    float Track;
    cin>>Track;


    cout<<"Enter wind speed: ";
    float Wind_speed;
    cin>>Wind_speed;


    cout<<"Enter the wind direction (in degrees): ";
    float wind_direction;
    cin>>wind_direction;


    cout<<"Enter the distance (in nutical miles): ";
    float distance;
    cin>>distance;


    cout<<"Enter the fuel flow rate (in gallons per hour): ";
    float fuel_flow_rate;
    cin>>fuel_flow_rate;

    //##############################

    float True_air_speed_result = True_air_speed(IAS , altitude);
    cout<<"The True Air Speed = "<<True_air_speed_result<<"\n";


    float Drift_angle_result = Drift_angle(Wind_speed , wind_direction , True_air_speed_result , Track);
    cout<<"The Drift Angle = "<<Drift_angle_result<<"\n";

    
    float True_heading_result = True_Heading(Track , Drift_angle_result);
    cout<<"The True Heading = "<<True_heading_result<<"\n";

    float Ground_speed_result = Ground_speed(True_air_speed_result,Drift_angle_result,Wind_speed,wind_direction,Track);
    cout<<"The Ground speed = "<<Ground_speed_result<<"\n";
    if (Ground_speed_result <= 0){
    cout<<"Flight cannot proceed due to invalid ground speed\n";
    return 0;
}

    float Time_result = Time(distance , Ground_speed_result);
    cout<<"The time to reach the destination = "<<Time_result<<" hours\n";


    float fuel_consumed_result = fuel_consumption(Time_result , fuel_flow_rate);
    cout<<"The fuel consumed = "<<fuel_consumed_result<<" gallons\n";

    cout<<"Have a safe flight Captain "<<Name<<"\n";
    return 0;
}