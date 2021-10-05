/*****************************************************************************/
/*!
\file   Ocean.cpp
\author Joe Centeno
\par    email: joe.centeno\@digipen.edu
\par    DigiPen login: joe.centeno
\par    Course: CS170
\par    Section: A
\par    Assignment #1
\date   5/25/2021

\brief  
  This file contains the implementation of the following functions for the 
   WAR BOATS assignment.
      
    Functions include:
    
       + CreateOcean(int num_boats, int x_quadrants, int y_quadrants)

       + DestroyOcean(Ocean *theOcean)

       + TakeShot(Ocean &ocean, const Point &coordinate)

       + PlaceBoat(Ocean &ocean, const Boat& boat)

       + GetShotStats(const Ocean &ocean)

       + DumpOcean(const CS170::WarBoats::Ocean& ocean,
            int field_width,
            bool extraline,
            bool showboats)
    
  Hours spent on this assignment: I spent around 9 hours over three 
   days

  Specific portions that gave you the most trouble: 
   The PlaceBoat function took me around 3 hours just to get working 
   and at first was very hard to visualize so I had to write persudo 
   code before hand to help. Ive gained a much better understanding of scope
  
  
*/
/*****************************************************************************/

#include "WarBoats.h" // Point, Boat, ShotStats Structs and Function Headers
#include "Ocean.h"    // Ocean Struct
#include <iostream>   // cout, endl
#include <iomanip>    // setw

namespace CS170
{
    namespace WarBoats
    {
        const int BOAT_LENGTH = 4;  //!< Length of a boat
        const int HIT_OFFSET = 100; //!< Add this to the boat ID

        /*
         * ALL STUDENT IMPLEMENTATION GOES HERE
         */

/**************************************************************************/
/*!
\fn Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)

\brief
  Creates Ocean for WAR BOATS game

\param num_boats
  Number of Boats

\param x_quadrants
  X Quadrant for Game

\param y_quadrants
  Y Quadrant for Game
  */
/**************************************************************************/
         Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
         {
             //Grid Size Var for Cleaner Code
            int GridSize = x_quadrants * y_quadrants;

             //Making Ocean
            Ocean *oceanPTR = new Ocean;
          
             //Setting Number of Boats in the Struct
            oceanPTR -> boats = new Boat[num_boats];

             //Setting the Number of Boats Var
            oceanPTR -> num_boats = num_boats;

             //Setting the Hieght and Width of the Board
            oceanPTR -> x_quadrants = x_quadrants;
            oceanPTR -> y_quadrants = y_quadrants;

             //Making the Grid from a 2D Array
            oceanPTR -> grid = new int[GridSize]; 
          
             //Init the Stats for the Game
            oceanPTR -> stats.hits = 0;
            oceanPTR -> stats.misses = 0;
            oceanPTR -> stats.sunk = 0;
            oceanPTR -> stats.duplicates = 0;
          
            //Init Boats
            for(int BoatIndex = 1; BoatIndex <= num_boats; BoatIndex++)
            {
              oceanPTR ->boats[BoatIndex - 1].ID = 0;   //Init the ID
              oceanPTR ->boats[BoatIndex - 1].hits = 0; //Init Hits

               //Init X & Y Position
              oceanPTR ->boats[BoatIndex - 1].position.x = 0;
              oceanPTR ->boats[BoatIndex - 1].position.y = 0;
            }
            
            //Init the Grid
            for(int InitGrid = 0; InitGrid < GridSize; InitGrid++)
            {
              oceanPTR -> grid[InitGrid] = 0;
            }

            return oceanPTR; //Return the Pointer to the Board Struct
         }

/**************************************************************************/
/*!
\fn void DestroyOcean(Ocean *theOcean)
           
\brief
 Uses Delete Operator to Destroy the Ocean

\param theOcean
  The Ocean Board
*/
/**************************************************************************/
         void DestroyOcean(Ocean *theOcean)
         {
            delete [] theOcean->boats; //Delets the Boats

            delete [] theOcean->grid;  //Delets the Grid

            delete theOcean;           //Delets the Ocean
         }

/**************************************************************************/
/*!
\fn ShotResult TakeShot(Ocean &ocean, const Point &coordinate)

\brief
  Calculates Shot in WAR BOATS game

\param ocean
  Adress of Ocean Board

\param coordinate
  Adress of Cordinates 
*/
/**************************************************************************/
         ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
         {
             //Set Grid Index
            int GridIndex = (coordinate.y * ocean.x_quadrants + coordinate.x);
             
             //Set Grid Value
            int GridValue = ocean.grid[GridIndex];

             //If Shot is Off Grid or Shot is Not on Board
             if ((coordinate.x < 0 || coordinate.y < 0) || 
                (coordinate.x > ocean.x_quadrants || 
                 coordinate.y > ocean.y_quadrants))
                 {
                   return srILLEGAL; //Return ILLEGAL
                 }
                
              //Shot Missed Boat
             if (GridValue == dtOK)
              {
                ocean.stats.misses++;
                ocean.grid[GridIndex] = -1;
               
                return srMISS; //Return MISS
              }
      
              //Shot Hit Boat
            if (GridValue > dtOK && GridValue <= ocean.num_boats)
             {
                ocean.grid[GridIndex] += 100;      
                ocean.stats.hits++;                // Increment Hits in Stats
                ocean.boats[GridValue - 1].hits++; // Increment Hits On Boats
              
                if(ocean.boats[GridValue - 1].hits == BOAT_LENGTH)
                {
                  ocean.stats.sunk++; // Increment Sunk

                  return srSUNK; // Return SUNK
                }
  
                return srHIT; // Return HIT
             }
      
             //Duplicate
            if (GridValue == dtBLOWNUP || GridValue > HIT_OFFSET)
            {
              ocean.stats.duplicates++; // Increment Duplicate

              return srDUPLICATE; // Return DUPLICATE
            }
      
            return srILLEGAL; // If No Condition Are Vaild Return ILLEGAL
          }

/**************************************************************************/
/*!
\fn BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)

\brief
  Places boats on the Ocean Board for WAR BOAT game

\param ocean
  Adress of Ocean Board

\param boat
  Adress of Boats 
 */
/**************************************************************************/
         BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
         {
             int PosY = boat.position.y; // Y Position for Boats
             int PosX = boat.position.x; // X Position for Boats

             int GridWidth = ocean.x_quadrants; // Grid Width
             
              // If the Boat is Vertical
             if(boat.orientation == oVERTICAL)
             {
                 // Top of Board
                if(boat.position.y >= 0 &&
                   boat.position.y <= ocean.y_quadrants)
                {
                    // Top of Board
                   if(boat.position.x >= 0 &&
                      boat.position.x <= ocean.x_quadrants)
                   {
                      // Bottom of Board
                     if(boat.position.y + 3 < ocean.y_quadrants)
                     {
                         // Safe Spots On Board
                        int SafeSpots = 0;
              
                          // Looping to see If a Spot is Empty
                         for(int i = 0; i <= 3; i++)
                         {
                            if(ocean.grid[(PosY + i) * GridWidth + PosX] == 0)
                              SafeSpots++;
                
                             // If All Spots Empty 
                            if (SafeSpots == BOAT_LENGTH)
                            {
                              // Loops through Writting Boat ID
                              for(int WriteGrid = 0; 
                                  WriteGrid <= 3; WriteGrid++)
                              {
                                 ocean.grid[(PosY + WriteGrid) * GridWidth 
                                 + PosX] = boat.ID;
                              }
                            
                              return bpACCEPTED; // Return ACCEPTED
                            }
                  
                          }
                      }
                    }
                 }
              }
           
               // If the Boat is Horizontal
              if(boat.orientation == oHORIZONTAL)
              {
                 // If on Left Of Board X
                if(boat.position.x >= 0 && 
                   boat.position.x <= ocean.x_quadrants)
                {
                   // If on Left Of Board Y
                  if(boat.position.y >= 0 &&
                     boat.position.y <= ocean.y_quadrants)
                  {
                     // If Right on Board
                    if(boat.position.x + 3 < ocean.x_quadrants)
                    {
                       // Safe Spots On Board
                      int SafeSpots = 0;
              
                       // Looping to see If a Spot is Empty
                      for(int j = 0; j <= 3; j++)
                      {
                         // If Nothing Check Again
                        if (ocean.grid[PosY * GridWidth + (PosX + j)] == 0)
                          SafeSpots++;
                
                         // If All Spots Empty 
                        if (SafeSpots == BOAT_LENGTH)
                        {
                          // Loops through Writting Boat ID
                          for (int write_h = 0; write_h <= 3; write_h++)
                          {
                            ocean.grid[PosY * GridWidth + 
                            (PosX + write_h)] = boat.ID;
                          }
                            
                          return bpACCEPTED; // Return ACCEPTED
                        }
                      }
                    }
                  }
                }
              }

            return bpREJECTED; // Return REJECTED
          }

/**************************************************************************/
/*!
\fn ShotStats GetShotStats(const Ocean &ocean)

\brief
 Gets the Shot Stats 

\param ocean
 The Adress of Ocean Board
*/
/**************************************************************************/
         ShotStats GetShotStats(const Ocean &ocean)
         {
            return ocean.stats; // Return Shot Stats
         }

/**************************************************************************/
/*!
\fn void DumpOcean(const CS170::WarBoats::Ocean& ocean,
            int field_width,
            bool extraline,
            bool showboats)

\brief
 Prints the grid (ocean) to the screen.

\param ocean
 The Ocean to print

\param field_width
 How much space each position takes when printed.

\param extraline
 If true, an extra line is printed after each row. If false, no extra
 line is printed.

\param showboats
 If true, the boats are shown in the output. (Debugging feature)
*/
/**************************************************************************/
        void DumpOcean(const CS170::WarBoats::Ocean& ocean,
            int field_width,
            bool extraline,
            bool showboats)
        {
            // For each row
            for (int y = 0; y < ocean.y_quadrants; y++)
            {
                // For each column
                for (int x = 0; x < ocean.x_quadrants; x++)
                {
                    // Get value at x/y position
                    int value = ocean.grid[y * ocean.x_quadrants + x];

                    // Is it a boat that we need to keep hidden?
                    if ((value > 0) && (value < HIT_OFFSET) 
                        && (showboats == false))
                        value = 0;

                    std::cout << std::setw(field_width) << value;
                }
                std::cout << std::endl;
                if (extraline)
                    std::cout << std::endl;
            }
        }

    } // namespace WarBoats
} // namespace CS170