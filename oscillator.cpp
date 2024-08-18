#include <iostream>
#include <cmath>
#include <fstream>

class WaveGenerator {
 private:
   float frequency;
   float amplitude;
   int sampleRate;
   float offset;
   float angle;

 public:
   WaveGenerator(float freq, float amp, int sr)
   : frequency(freq), amplitude(amp), sampleRate(sr) {
	offset = 2 * 3.141592653589793238462643383279502884 * frequency / sampleRate;
	angle = 0.0;
   }
   float getNextSample() {
	float sample = amplitude * sin(angle);
	angle += offset;
	return sample/0.8;
   }
   void printValues() {
	std::cout<<"Frequency "<<frequency<<std::endl;
	std::cout<<"Amplitude "<<amplitude<<std::endl;
	std::cout<<"Sample Rate "<<sampleRate<<std::endl;
   }
};

int main(int argc, char** argv) {
  if(argc < 7){
   std::cout<<"Enter frequency, amplitude, sample rate, duration, bit depth(8/16/24/32) and filename in respective order"<<std::endl;
   return 1;
  }
  int sampleRate = atoi(argv[3]);
  float frequency = atof(argv[1]);
  float amplitude = atof(argv[2]);
  float duration = atof(argv[4]);
  int bitDepth = atoi(argv[5]);
  char* fileName = argv[6];
  std::ofstream outFile(fileName, std::ios::binary);
  WaveGenerator firstWave(frequency, amplitude, sampleRate);
  firstWave.printValues();
  int maxAmplitude = pow(2, bitDepth-1)-1;
  std::cout<<"Writing data to file : "<<fileName<<std::endl;
  for(int i=0; i<sampleRate * duration; i++) {
	float sample = firstWave.getNextSample();
	int integerSample = static_cast<int>(sample * maxAmplitude);
	outFile.write(reinterpret_cast<char*> (&integerSample), bitDepth/8);
	//std::cout<<"Sample "<<i+1<<":\t"<<sample<<std::endl;
  }
  std::cout<<"Writing completed"<<std::endl;
  outFile.close();
  return 0;
}
