//
// Poisson Disk Points Generator
//
// \version 1.1.4
// \date 19/10/2016
// \author Sergey Kosarevsky, 2014-2016
// \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
//
// Fast Poisson Disk Sampling in Arbitrary Dimensions
// http://people.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf

// Implementation based on http://devmag.org.za/2009/05/03/poisson-disk-sampling/

/* Versions history:
 *		1.1.4 	Oct 19, 2016		POISSON_PROGRESS_INDICATOR can be defined outside of the header file, disabled by default
 *		1.1.3a	Jun  9, 2016		Update constructor for DefaultPRNG
 *		1.1.3		Mar 10, 2016		Header-only library, no global mutable state
 *		1.1.2		Apr  9, 2015		Output a text file with XY coordinates
 *		1.1.1		May 23, 2014		Initialize PRNG seed, fixed uninitialized fields
 *    1.1		May  7, 2014		Support of density maps
 *		1.0		May  6, 2014
 */

#ifndef PoissonGenerator_hpp
#define PoissonGenerator_hpp

#include <stdio.h>
#include <vector>
#include <random>
#include <stdint.h>
#include <time.h>

namespace PoissonGenerator
{
    class DefaultPRNG
    {
    public:
        DefaultPRNG()
        : m_Gen( std::random_device()() )
        , m_Dis( 0.0f, 1.0f )
        {
            // prepare PRNG
            m_Gen.seed( (int)time( nullptr ) );
        }
        
        explicit DefaultPRNG( uint32_t seed )
        : m_Gen( seed )
        , m_Dis( 0.0f, 1.0f )
        {
        }
        
        float RandomFloat();
        
        int RandomInt( int Max );
        
    private:
        std::mt19937 m_Gen;
        std::uniform_real_distribution<float> m_Dis;
    };
    
    struct sPoint
    {
        sPoint()
        : x( 0 )
        , y( 0 )
        , m_Valid( false )
        {}
        sPoint( float X, float Y )
        : x( X )
        , y( Y )
        , m_Valid( true )
        {}
        float x;
        float y;
        bool m_Valid;
        //
        bool IsInRectangle() const
        {
            return x >= 0 && y >= 0 && x <= 1 && y <= 1;
        }
        //
        bool IsInCircle() const
        {
            float fx = x - 0.5f;
            float fy = y - 0.5f;
            return ( fx*fx + fy*fy ) <= 0.25f;
        }
    };
    
    struct sGridPoint
    {
        sGridPoint( int X, int Y )
        : x( X )
        , y( Y )
        {}
        int x;
        int y;
    };
    
    float GetDistance( const sPoint& P1, const sPoint& P2 );
    sGridPoint ImageToGrid( const sPoint& P, float CellSize );
    
    
    struct sGrid
    {
        sGrid( int W, int H, float CellSize )
        : m_W( W )
        , m_H( H )
        , m_CellSize( CellSize )
        {
            m_Grid.resize( m_H );
            
            for ( auto i = m_Grid.begin(); i != m_Grid.end(); i++ ) { i->resize( m_W ); }
        }
        void Insert( const sPoint& P )
        {
            sGridPoint G = ImageToGrid( P, m_CellSize );
            m_Grid[ G.x ][ G.y ] = P;
        }
        bool IsInNeighbourhood( sPoint Point, float MinDist, float CellSize )
        {
            sGridPoint G = ImageToGrid( Point, CellSize );
            
            // number of adjucent cells to look for neighbour points
            const int D = 5;
            
            // scan the neighbourhood of the point in the grid
            for ( int i = G.x - D; i < G.x + D; i++ )
            {
                for ( int j = G.y - D; j < G.y + D; j++ )
                {
                    if ( i >= 0 && i < m_W && j >= 0 && j < m_H )
                    {
                        sPoint P = m_Grid[ i ][ j ];
                        
                        if ( P.m_Valid && GetDistance( P, Point ) < MinDist ) { return true; }
                    }
                }
            }
            
            
            return false;
        }
        
    private:
        int m_W;
        int m_H;
        float m_CellSize;
        
        std::vector< std::vector<sPoint> > m_Grid;
    };
    
    template <typename PRNG>
    sPoint PopRandom( std::vector<sPoint>& Points, PRNG& Generator );
    
    template <typename PRNG>
    sPoint GenerateRandomPointAround( const sPoint& P, float MinDist, PRNG& Generator );
    
    /**
     Return a vector of generated points
     
     NewPointsCount - refer to bridson-siggraph07-poissondisk.pdf for details (the value 'k')
     Circle  - 'true' to fill a circle, 'false' to fill a rectangle
     MinDist - minimal distance estimator, use negative value for default
     **/
//    template <typename PRNG>
    std::vector<sPoint> GeneratePoissonPoints(
                                              size_t NumPoints,
            DefaultPRNG& Generator
                                                     );
}


#endif /* PoissonGenerator_hpp */
