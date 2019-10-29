#include "../include/life_game.h"

namespace life
{
//*NAMESPACE LIFE*//


// Constructor using struct options.
LifeConfig::LifeConfig(Options origin_life)
{
  firstMan = origin_life;

  //Create cells table with borther, after now use for(1 to <= size()) to represent firstMan
  firstManCells.resize(firstMan.nLin + 2, std::vector<Cell>(firstMan.nCol+2));
  firstManChars.resize(firstMan.nLin, std::vector<char>(firstMan.nCol));

  //rendering alives
  for(int i = 0; i < firstMan.starter_config.size(); i++){
      for(int j = 0; j < firstMan.starter_config[0].size(); j++){
          if(firstMan.starter_config[i][j] == firstMan.aliveCell){
              firstManCells[i+1][j+1].Status = true; // iterator+1 --> avoid safe border.
        }
    }
  }


  RenderNeighbours();
  RenderCharTable(firstManChars);
  //printNeighboursTable(); // function for tests.
}

void LifeConfig::assign( Options origin_life )
{
  firstMan = origin_life;

  //Create cells table with borther, after now use for(1 to <= size()) to represent firstMan
  firstManCells.resize(firstMan.nLin + 2, std::vector<Cell>(firstMan.nCol+2));
  firstManChars.resize(firstMan.nLin, std::vector<char>(firstMan.nCol));

  //rendering alives
  for(int i = 0; i < firstMan.starter_config.size(); i++){
      for(int j = 0; j < firstMan.starter_config[0].size(); j++){
          if(firstMan.starter_config[i][j] == firstMan.aliveCell){
              firstManCells[i+1][j+1].Status = true; // iterator+1 --> avoid safe border.
        }
    }
  }


  RenderNeighbours();
  RenderCharTable(firstManChars);
  //printNeighboursTable(); // function for tests.
}



// Check number of neighbours.
void LifeConfig::RenderNeighbours(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){

        //reset neighbours
        firstManCells[i][j].neighbours = 0;

        //increment neighbour count each alive cell.
        if(firstManCells[i-1][j].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i-1][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i-1][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
    }
  }
}


// Applying life rules.
void LifeConfig::RefreshGeneration(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){
      //Rule 1
      if ( ( firstManCells[i][j].Status == true ) and ( firstManCells[i][j].neighbours <= 1 ) ){
        firstManCells[i][j].Status = false;
      }
      //Rule 2
      else if ( ( firstManCells[i][j].Status == true ) and ( firstManCells[i][j].neighbours >= 4 )){
        firstManCells[i][j].Status = false;
      }
      //Rule 3
      else if ( ( firstManCells[i][j].Status == true ) and ( ( firstManCells[i][j].neighbours == 2 ) or ( firstManCells[i][j].neighbours == 3) ) ){
        firstManCells[i][j].Status = true;
      }
      //Rule 4
      else if ( ( firstManCells[i][j].Status == false ) and ( firstManCells[i][j].neighbours == 3 ) ){
        firstManCells[i][j].Status = true;
      }
    }
  }

  RenderNeighbours();
  RenderCharTable(firstManChars);
  genNumber++;
}


// Render next generation.
void LifeConfig::RenderCharTable(std::vector<std::vector<char>> &myCharVector)
{
  aliveCells = 0;

  firstMan.coordinates.clear();

  for(int i = 0; i < myCharVector.size(); i++)
  {
      for(int j = 0; j < myCharVector[i].size(); j++)
      {
          if(firstManCells[i+1][j+1].Status == true)
          {
              aliveCells++; // increment to verify the extinction.
              myCharVector[i][j] = firstMan.aliveCell;
              firstMan.coordinates.push_back( std::make_pair( i, j ) );
          }else{
              myCharVector[i][j] = ' ';
          }
    }
  }
}


void LifeConfig::PrintTable()
{
  std::cout << "\nGeneration " << genNumber << "\n";

  for( int i = 0; i < firstMan.nLin; i++ )
  {
      std::cout << "[";

      for( int j = 0; j < firstMan.nCol; j++ )
      {
          if( firstManChars[i][j] != firstMan.aliveCell )
          {
              std::cout << " ";
          }
          else
            std::cout << firstManChars[i][j];
      }
      std::cout << "]" << std::endl;
  }
}


void LifeConfig::printNeighboursTable(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){
      if( firstManCells[i][j].neighbours == 0 )
      {
          std::cout << " ";
      }
      else
      std::cout << firstManCells[i][j].neighbours << " ";
    }
    std::cout << std::endl;
  }
}


void LifeConfig::writeFile( std::string filename, size_t genNumber, std::string dirpath )
{
    std::string genNum = std::to_string( genNumber );

    std::ofstream outFile;

    if( dirpath != "" )
    {
        outFile.open("../"+dirpath+"/"+filename+"_"+genNum+".txt");
    }
    else
        outFile.open("../output/"+filename+"_"+genNum+".txt");

    outFile << "\n\n";

    for( int i = 0; i < firstMan.nLin; i++ )
    {
        outFile << "[";

        for( int j = 0; j < firstMan.nCol; j++ )
        {
            if( firstManChars[i][j] != firstMan.aliveCell )
            {
                outFile << " ";
            }
            else
                outFile << firstManChars[i][j];
        }
        outFile << "]" << std::endl;
  }

  outFile.close();
}
//*END NAMESPACE LIFE*//
} // namespace life
