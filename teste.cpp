#include <iostream>
#include <vector>
#include "include/common.h"

using namespace std;

int main(){
  typedef unsigned char component_t;
  
  size_t m_width;    //!< The image width in pixel units.
  size_t m_height;   //!< The image height in pixel units.
  short m_block_size; //!< The virtual pixel size in pixels
  // TODO: If you wish to use a 3D matrix instead of an array, this is where
  // you should replace the vector with the 3D matrix.

  component_t n = 8;
  
  vector<vector<life::Color>> m_pixels; //!< The pixels, stored as 4 RGBA components.

  m_pixels.resize(n);
  for(int i = 0; i < n; i++){
    m_pixels[i].resize(n);
  }

  //chaging value in .clear function
  m_pixels[0][0].channels[0] = 55;
  m_pixels[0][0].channels[1] = 55;
  m_pixels[0][0].channels[2] = 55;

  cout << (int)m_pixels[0][0].channels[0] << endl;
  cout << (int)m_pixels[0][0].channels[1] << endl;
  cout << (int)m_pixels[0][0].channels[2] << endl;

  cout << (int)life::color_pallet["BLACK"].channels[0] << endl;
  cout << (int)life::color_pallet["BLACK"].channels[1] << endl;
  cout << (int)life::color_pallet["BLACK"].channels[2] << endl;
  cout << (int)life::color_pallet["BLACK"].channels[3] << endl;

  cout << (int)life::BLACK.channels[0] << " ";
  cout << (int)life::BLACK.channels[1] << " ";
  cout << (int)life::BLACK.channels[2] << " \n";

  cout << "life::colorpallet\n";
  cout << life::color_pallet["black"] << endl;

  std::vector<vector<int>> v1;

  v1.resize(10);
  auto IT_v1 = v1.data();





  /*
  Canvas canv{ 20, 15, 50 };          // Cria um canvas com W=20 x H=15 e block size = 50.

  canv.clear( YELLOW );               // Pinta todo canvas de amarelo.
  canv.pixel( Point2{ 8, 5}, BLUE );  // Solicita que o pixel (8,5) seja pintado de azul.
  */
  
}