//
// Poisson Disk Points Generator
//
// \version 1.1.4
// \date 19/10/2016
// \author Sergey Kosarevsky, 2014-2016
// \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
//

#include "PoissonGenerator.hpp"
namespace PoissonGenerator
{
    float DefaultPRNG::RandomFloat()
    {
        return static_cast<float>( m_Dis( m_Gen ) );
    }
    
    int DefaultPRNG::RandomInt( int Max )
    {
        std::uniform_int_distribution<> DisInt( 0, Max );
        return DisInt( m_Gen );
    }
    
    float GetDistance( const sPoint& P1, const sPoint& P2 )
    {
    	return sqrt( ( P1.x - P2.x ) * ( P1.x - P2.x ) + ( P1.y - P2.y ) * ( P1.y - P2.y ) );
    }
    
    sGridPoint ImageToGrid( const sPoint& P, float CellSize )
    {
    	return sGridPoint( ( int )( P.x / CellSize ), ( int )( P.y / CellSize ) );
    }
    
    template <typename PRNG>
    sPoint PopRandom( std::vector<sPoint>& Points, PRNG& Generator )
    {
    	const int Idx = Generator.RandomInt( (int)Points.size()-1 );
    	const sPoint P = Points[ Idx ];
    	Points.erase( Points.begin() + Idx );
    	return P;
    }
    
    template <typename PRNG>
    sPoint GenerateRandomPointAround( const sPoint& P, float MinDist, PRNG& Generator )
    {
    	// start with non-uniform distribution
    	float R1 = Generator.RandomFloat();
    	float R2 = Generator.RandomFloat();
    
    	// radius should be between MinDist and 2 * MinDist
    	float Radius = MinDist * ( R1 + 1.0f );
    
    	// random angle
    	float Angle = 2 * 3.141592653589f * R2;
    
    	// the new point is generated around the point (x, y)
    	float X = P.x + Radius * cos( Angle );
    	float Y = P.y + Radius * sin( Angle );
    
    	return sPoint( X, Y );
    }
    
//    template <typename PRNG>
    std::vector<sPoint> GeneratePoissonPoints(size_t NumPoints,
            DefaultPRNG& Generator){
        int NewPointsCount = 30;
        bool Circle = true;
        float MinDist = -1.0f;
        if ( MinDist < 0.0f )
        {
            MinDist = sqrt( float(NumPoints) ) / float(NumPoints);
        }

        std::vector<sPoint> SamplePoints;
        std::vector<sPoint> ProcessList;

        // create the grid
        float CellSize = MinDist / sqrt( 2.0f );

        int GridW = ( int )ceil( 1.0f / CellSize );
        int GridH = ( int )ceil( 1.0f / CellSize );

        sGrid Grid( GridW, GridH, CellSize );

        sPoint FirstPoint;
        do {
            FirstPoint = sPoint( Generator.RandomFloat(), Generator.RandomFloat() );
        } while (!(Circle ? FirstPoint.IsInCircle() : FirstPoint.IsInRectangle()));

        // update containers
        ProcessList.push_back( FirstPoint );
        SamplePoints.push_back( FirstPoint );
        Grid.Insert( FirstPoint );

        // generate new points for each point in the queue
        while ( !ProcessList.empty() && SamplePoints.size() < NumPoints )
        {
    #if POISSON_PROGRESS_INDICATOR
            // a progress indicator, kind of
            if ( SamplePoints.size() % 100 == 0 ) std::cout << ".";
    #endif // POISSON_PROGRESS_INDICATOR

            sPoint Point = PopRandom( ProcessList, Generator );

            for ( int i = 0; i < NewPointsCount; i++ )
            {
                sPoint NewPoint = GenerateRandomPointAround( Point, MinDist, Generator );

                bool Fits = Circle ? NewPoint.IsInCircle() : NewPoint.IsInRectangle();

                if ( Fits && !Grid.IsInNeighbourhood( NewPoint, MinDist, CellSize ) )
                {
                    ProcessList.push_back( NewPoint );
                    SamplePoints.push_back( NewPoint );
                    Grid.Insert( NewPoint );
                    continue;
                }
            }
        }

    #if POISSON_PROGRESS_INDICATOR
        std::cout << std::endl << std::endl;
    #endif // POISSON_PROGRESS_INDICATOR

        return SamplePoints;
    }
    

}
