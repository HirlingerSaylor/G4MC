#include <fstream>
using namespace std;

main(){
  ofstream OUTFILE;
  OUTFILE.open("uni_hallbfield.dat");
  for(int i = 0; i < 300; i++){
    for(int j = 0; j < 300; j++){
      OUTFILE << i << " " << j << " " << 0 << " " << 0 << " " << 0 << endl;
    }
  }

  OUTFILE.close();
}
