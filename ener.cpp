#include<iostream>
#include<string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

void increment(int** lattice, int length, int width, int row)
{
    
    for (int i = width - 2; i >= 0; i--)
    {
        if (lattice[row][i] == 0)
        {
            lattice[row][i] = 1;
            return;
        }
        else if(lattice[row][i] == 1)
        {
            lattice[row][i]  = 0;
        }
       
        if (i == 0 && row > 1)
        {
            increment(lattice, length, width, row - 1 );
            return;
        }
        
    }
    return;
}
    
void incrementB(int** lattice, int length, int width, int row, int lengthA, int widthA)
{
    if (length - 2 - row < lengthA)
    {
        for (int i = width - 2 - widthA; i >= 0; i--)
        {
        	if (lattice[row][i] == 0)
        	{
        	    lattice[row][i] = 1;
        	    return;
        	}
        	else if(lattice[row][i] == 1)
        	{
        	    lattice[row][i]  = 0;
        	}
       	
        	if (i == 0 && row > 1)
        	{
        	    incrementB(lattice, length, width, row - 1, lengthA, widthA);
        	    return;
        	}
        
    	}
    }
    else 
    {
    	for (int i = width - 2; i >= 0; i--)
    	{
    	    if (lattice[row][i] == 0)
    	    {
    	        lattice[row][i] = 1;
    	        return;
    	    }
    	    else if(lattice[row][i] == 1)
    	    {
    	        lattice[row][i]  = 0;
    	    }
       
        	if (i == 0 && row > 1)
        	{
        	    incrementB(lattice, length, width, row - 1, lengthA, widthA);
        	    return;
        	}
        
    	}
    }
    return;
}

double* EnerEntro(double b, double temperature, int length, int width)
{
    double* retArray = new double[4];
    length += 2;
    width += 2;
    double ener = 0;
    double averageEnerNum = 0;
    double averageEnerDen = 0;
    int bext = 0;
    double avbext = 0;   
 
    int** lattice = new int*[length];
    for(int i = 0; i < length; ++i) {
        lattice[i] = new int[width];
    }
    for (int i = 0; i < length; i++) {
    	for (int j = 0; j < width; j++) {
        	lattice[i][j] = 0;
	}
    }
    
    for (int i = 0; i < length; i++)
    {
        lattice[i][0] = 2;
        lattice[i][width - 1] = 2;
    }
    for (int j = 0; j < width; j++)
    {
        lattice[0][j] = 2;
        lattice[length - 1][j] = 2;
    }
    
    for(int t = 0; t < pow(2, (length - 2) * (width - 2)) ; t++)
    {
        for(int l = length - 2; l > 0; l--)
        {
            for(int w = width - 2; w > 0; w--)
            {
                if(lattice[l][w] == 0)
                {
                    ener += b;
                    bext -= 1;
                }
                else if(lattice[l][w] == 1)
                {
                    ener -= b;
                    bext += 1;
                }
    
                if(lattice[l][w] == lattice[l - 1][w])
                {
                    ener -= 1;
                }
                else if(lattice[l][w] != 2 && lattice[l - 1][w] != 2)
                {
                    ener += 1;
                }
                
                if(lattice[l][w] == lattice[l][w - 1])
                {
                    ener -= 1;
                }
                else if(lattice[l][w] != 2 && lattice[l][w -1] != 2)
                {
                    ener += 1;
                }
            }
        }

        averageEnerNum += ener * exp((-1 * ener)/ temperature);
        averageEnerDen += exp((-1* ener) / temperature);
        avbext += bext * bext * exp((-1 * ener)/ temperature);        

        increment(lattice, length, width, length - 2);
        ener = 0;
        bext = 0;
    }
    retArray[1] = (averageEnerNum / averageEnerDen);
    retArray[0] = ((averageEnerNum / averageEnerDen)/temperature) + (log(averageEnerDen));
    retArray[2] = avbext / averageEnerDen;
    retArray[3] = averageEnerDen;

    for (int i = 0; i < length; i++) {
        delete [] lattice[i];
    }
    delete [] lattice;  
    lattice = 0;

    return retArray;
    
    
}

/*
double entroB(double b, double temperature, int length, int width, int lengthA, int widthA)
{
    length += 2;
    width += 2;
    double ener = 0;
    double averageEnerNum = 0;
    double averageEnerDen = 0;
    
    int** lattice = new int*[length];
    for(int i = 0; i < length; ++i)
        lattice[i] = new int[width];
    
    for (int i = 0; i < length; i++)
    {
        lattice[i][0] = 2;
        lattice[i][width - 1] = 2;
    }
    for (int j = 0; j < width; j++)
    {
        lattice[0][j] = 2;
        lattice[length - 1][j] = 2;
    }
    
    for (int c = length - 2; length - 2 - c < lengthA; c--)
    {
        for (int d = width - 2; width - 2 - d < widthA; d--)
        {   
            lattice[c][d] = 2;
        }
    } 
    
    for(int t = 0; t < pow(2, (((length - 2) * (width - 2)) - (lengthA * widthA))) ; t++)
    {
        for(int l = length - 2; l > 0; l--)
        {
            for(int w = width - 2; w > 0; w--)
            {
                if(lattice[l][w] == 0)
                {
                    ener += b;
                }
                else if(lattice[l][w] == 1)
                {
                    ener -= b;
                }
    
                if(lattice[l][w] == lattice[l - 1][w] && lattice[l][w] != 2 && lattice[l - 1][w] != 2)
                {
                    ener -= 1;
                }
                else if(lattice[l][w] != 2 && lattice[l - 1][w] != 2)
                {
                    ener += 1;
                }
                
                if(lattice[l][w] == lattice[l][w - 1] && lattice[l][w] != 2 && lattice[l][w -1] != 2)
                {
                    ener -= 1;
                }
                else if(lattice[l][w] != 2 && lattice[l][w -1] != 2)
                {
                    ener += 1;
                }
            }
        }
        averageEnerNum += ener * exp((-1 * ener)/ temperature);
        averageEnerDen += exp((-1* ener) / temperature);
        
        incrementB(lattice, length, width, length - 2, lengthA, widthA);

        ener = 0;
    }

    
    for (int i = 0; i < length; i++) {
        delete [] lattice[i];
    }
    delete [] lattice;  
    lattice = 0;

    return ((averageEnerNum / averageEnerDen)/temperature) + (log(averageEnerDen));
    
    
}
*/



double entroB(double b, double temperature, int length, int width, int lengthA, int widthA)
{
    length += 2;
    width += 2;
    double ener = 0;
    double averageEnerNum = 0;
    double averageEnerDen = 0;
    
    int** lattice = new int*[length];
   // Create new array
    for(int i = 0; i < length; ++i)
         lattice[i] = new int[width];

    // Initialize array
    
    for (int i = 0; i < length; i++) {
    	for (int j = 0; j < width; j++) {
        	lattice[i][j] = 0;
	}
    }

    
    for (int i = 0; i < length; i++)
    {
        lattice[i][0] = 2;
        lattice[i][width - 1] = 2;
    }
    for (int j = 0; j < width; j++)
    {
        lattice[0][j] = 2;
        lattice[length - 1][j] = 2;
    }
    
    for(int t = 0; t < pow(2, (((length - 2) * (width - 2)) - (lengthA * widthA))) ; t++)
    {
        for(int l = length - 2; l > 0; l--)
        {
            if (length - 2 - l < lengthA){
            	for(int w = width - 2 - widthA; w > 0; w--)
            	{
            	    if(lattice[l][w] == 0)
            	    {
            	        ener += b;
            	    }
            	    else if(lattice[l][w] == 1)
            	    {
            	        ener -= b;
            	    }
    	           if(l - 1 >= 0)
                   {
     	           	if(lattice[l][w] == lattice[l - 1][w])
       	           	{
       	           	     ener -= 1;
       	           	}
       	           	else if(lattice[l][w] != 2 && lattice[l - 1][w] != 2)
       	           	{
       	           	     ener += 1;
       	           	}
                   }
       	           if(w - 1 >= 0)
                   {	
       	         	if(lattice[l][w] == lattice[l][w - 1])
       	         	{
       	         	     ener -= 1;
   	         	}
      	         	else if(lattice[l][w] != 2 && lattice[l][w -1] != 2)
      	         	{
     	         	     ener += 1;
     	         	}
                   }
     	        }
             }
            else
            {
            	for(int w = width - 2; w > 0; w--)
            	{
                	if(lattice[l][w] == 0)
                	{
                	    ener += b;
                	}
                	else if(lattice[l][w] == 1)
                	{
                	    ener -= b;
                	}
    	
                	if(lattice[l][w] == lattice[l - 1][w])
                	{
                	    ener -= 1;
                	}
                	else if(lattice[l][w] != 2 && lattice[l - 1][w] != 2)
                	{
                	    ener += 1;
                	}
                
                	if(lattice[l][w] == lattice[l][w - 1])
                	{
                	    ener -= 1;
                	}
                	else if(lattice[l][w] != 2 && lattice[l][w -1] != 2)
                	{
                	    ener += 1;
                	}
            	}
           
            }
        }
        averageEnerNum += ener * exp((-1 * ener)/ temperature);
        averageEnerDen += exp((-1* ener) / temperature);
        //cout << ener << endl;
        //cout << averageEnerNum << " " << averageEnerDen << endl;

        incrementB(lattice, length, width, length - 2, lengthA, widthA);
        ener = 0;
    }
    
    for (int i = 0; i < length; i++) {
        delete [] lattice[i];
    }
    delete [] lattice;  
    lattice = 0;

    return ((averageEnerNum / averageEnerDen)/temperature) + (log(averageEnerDen));
    
    
}  



/*void incrementTest(int length, int width)
{
    int** lattice = new int*[length];

    length += 2;
    width += 2;

    for(int i = 0; i < length; ++i)
        lattice[i] = new int[width];
    
    for (int i = 0; i < length; i++)
    {
        lattice[i][0] = 2;
        lattice[i][width - 1] = 2;
    }
    for (int j = 0; j < width; j++)
    {
        lattice[0][j] = 2;
        lattice[length - 1][j] = 2;
    }
    
    for(int t = 0; t < pow(2, (length - 2) * (width - 2)) ; t++)
    {
        for(int l = length - 2; l > 0; l--)
        {
            for(int w = width - 2; w > 0; w--)
            {
                cout << lattice[l][w] << endl;
            }   
        }
        
        increment(lattice, length, width, length - 2);
        cout << endl;
    }

    for (int i = 0; i < length; i++) {
        delete [] lattice[i];
    }
    delete [] lattice;  
    lattice = 0;

    return;
}*/

int main()
{
    int length = 0;
    int width = 0;
    double upperTemp = 0;
    double temperature=0;
    double b = 0;
    int lengthA = 0;
    int widthA = 0;
    double *enerEntro;
    double *enerEntroA;
    double Tmax = 0;
    double Imax = 0;
    
    ofstream enerFile;
    ofstream entroFile;
    ofstream IFile;
    //ofstream mag;
    ofstream bext;
    enerFile.open("ener2d.txt");
    entroFile.open("entro2d.txt");
    IFile.open("I2d.txt");
    //mag.open("mag2d.txt");
    bext.open("mag.txt");

    cout << "Enter the length of the two-dimensional lattice:  ";
    cin >> length;
    cout << "Enter the width of the two-dimensional lattice:  ";
    cin >> width;
    cout << "Enter the lower range of the temperature of the heat bath to plot: ";
    cin >> temperature;
    cout << "Enter the upper range of the temperature of the heat bath to plot: ";
    cin >> upperTemp;
    cout << "Enter the magnitude of the magnetic field: ";
    cin >> b;
    cout << "Enter the length of the lattice A (to measure mutual information with sublattice of size A:  ";
    cin >> lengthA;
    cout << "Enter the width of the lattice A (to measure mutual information with sublattice of size A:  ";
    cin >> widthA;
    


    while (temperature <= upperTemp){
        enerEntro = EnerEntro(b, temperature, length, width);
        enerEntroA = EnerEntro(b, temperature, lengthA, widthA);
    
        enerFile << temperature << " "<< *(enerEntro + 1)/(length*width) << endl; 
        entroFile << temperature << " "<< *(enerEntro + 0)/(length*width) << endl; 
        IFile << temperature << " " << (*(enerEntroA + 0) + entroB(b, temperature, length, width, lengthA, widthA) - *(enerEntro + 0))/(length*width) <<   endl;
        //mag << temperature << " " << *(enerEntro + 3)/(length*width) << endl;
        bext << temperature << " " << *(enerEntro + 2)/(length*length*width*width) << endl;
       

        temperature += .01;
        //cout << temperature << " " << entroB(b, temperature, length, width, lengthA, widthA) << endl;
	delete [] enerEntro;
        delete [] enerEntroA;
        
        if ((*(enerEntroA + 0) + entroB(b, temperature, length, width, lengthA, widthA) - *(enerEntro + 0))/(length*width) > Imax){
            Imax = (*(enerEntroA + 0) + entroB(b, temperature, length, width, lengthA, widthA) - *(enerEntro + 0))/(length*width);
            Tmax = temperature;
        }

        /*incrementTest(length, width);
        temperature += .01;*/
	
    }
cout << Imax << " " << Tmax << endl;
enerFile.close();
entroFile.close();
IFile.close();
//mag.close();
bext.close();

/*
system ("gnuplot  -p 'x.p'");
system ("gnuplot  -p 'x1.p'");
system ("gnuplot  -p 'x2.p'");
system ("gnuplot  -p 'x3.p'");
*/
 
}
