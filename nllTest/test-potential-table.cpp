#include <nll/nll.h>
#include <tester/register.h>

using namespace nll;
using namespace nll::core;
using namespace nll::algorithm;

class TestPotentialTable
{
public:
   void testMul1()
   {
      PotentialTable::VectorI domain1( 2 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 2;
      PotentialTable::VectorI multiplicity1( 2 );
      multiplicity1[ 0 ] = 3;
      multiplicity1[ 1 ] = 2;
      PotentialTable::VectorI domain2( 1 );
      domain2[ 0 ] = 1;
      PotentialTable::VectorI multiplicity2( 1 );
      multiplicity2[ 0 ] = 2;
      PotentialTable::Vector table( 6 );
      for ( size_t n = 0; n < table.size(); ++n )
      {
         table[ n ] = n + 1;
      }

      PotentialTable p1( table, domain1, multiplicity1 );
      PotentialTable p2 = p1.extendDomain( domain2, multiplicity2 );
      p2.getTable().print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 12 );
      TESTER_ASSERT( p2.getTable()[ 0 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 1 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 2 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 3 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 4 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 5 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 6 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 7 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 8 ] == 6 );
      TESTER_ASSERT( p2.getTable()[ 9 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 10 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 11 ] == 6 );
   }

   void testMul2()
   {
      PotentialTable::VectorI domain1( 2 );
      domain1[ 0 ] = 1;
      domain1[ 1 ] = 2;
      PotentialTable::VectorI multiplicity1( 2 );
      multiplicity1[ 0 ] = 3;
      multiplicity1[ 1 ] = 2;
      PotentialTable::VectorI domain2( 1 );
      domain2[ 0 ] = 0;
      PotentialTable::VectorI multiplicity2( 1 );
      multiplicity2[ 0 ] = 2;
      PotentialTable::Vector table( 6 );
      for ( size_t n = 0; n < table.size(); ++n )
      {
         table[ n ] = n + 1;
      }

      PotentialTable p1( table, domain1, multiplicity1 );
      PotentialTable p2 = p1.extendDomain( domain2, multiplicity2 );
      p2.getTable().print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 12 );
      TESTER_ASSERT( p2.getTable()[ 0 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 1 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 2 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 3 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 4 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 5 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 6 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 7 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 8 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 9 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 10 ] == 6 );
      TESTER_ASSERT( p2.getTable()[ 11 ] == 6 );
   }

   void testMul3()
   {
      PotentialTable::VectorI domain1( 2 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      PotentialTable::VectorI multiplicity1( 2 );
      multiplicity1[ 0 ] = 3;
      multiplicity1[ 1 ] = 2;
      PotentialTable::VectorI domain2( 1 );
      domain2[ 0 ] = 2;
      PotentialTable::VectorI multiplicity2( 1 );
      multiplicity2[ 0 ] = 2;
      PotentialTable::Vector table( 6 );
      for ( size_t n = 0; n < table.size(); ++n )
      {
         table[ n ] = n + 1;
      }

      PotentialTable p1( table, domain1, multiplicity1 );
      PotentialTable p2 = p1.extendDomain( domain2, multiplicity2 );
      p2.getTable().print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 12 );
      TESTER_ASSERT( p2.getTable()[ 0 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 1 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 2 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 3 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 4 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 5 ] == 6 );
      TESTER_ASSERT( p2.getTable()[ 6 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 7 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 8 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 9 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 10 ] == 5 );
      TESTER_ASSERT( p2.getTable()[ 11 ] == 6 );
   }

   void testMul4()
   {
      PotentialTable::VectorI domain1( 2 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 2;
      PotentialTable::VectorI multiplicity1( 2 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      PotentialTable::VectorI domain2( 2 );
      domain2[ 0 ] = 1;
      domain2[ 1 ] = 3;
      PotentialTable::VectorI multiplicity2( 2 );
      multiplicity2[ 0 ] = 2;
      multiplicity2[ 1 ] = 2;
      PotentialTable::Vector table( 4 );
      for ( size_t n = 0; n < table.size(); ++n )
      {
         table[ n ] = n + 1;
      }

      PotentialTable p1( table, domain1, multiplicity1 );
      PotentialTable p2 = p1.extendDomain( domain2, multiplicity2 );
      p2.getTable().print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 16 );
      TESTER_ASSERT( p2.getTable()[ 0 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 1 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 2 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 3 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 4 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 5 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 6 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 7 ] == 4 );

      TESTER_ASSERT( p2.getTable()[ 8 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 9 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 10 ] == 1 );
      TESTER_ASSERT( p2.getTable()[ 11 ] == 2 );
      TESTER_ASSERT( p2.getTable()[ 12 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 13 ] == 4 );
      TESTER_ASSERT( p2.getTable()[ 14 ] == 3 );
      TESTER_ASSERT( p2.getTable()[ 15 ] == 4 );
   }

   void testMul5()
   {
      // create p(B)=( 0.4, 0.6 )
      PotentialTable::VectorI domain1( 1 );
      domain1[ 0 ] = 1;
      PotentialTable::VectorI multiplicity1( 1 );
      multiplicity1[ 0 ] = 2;

      PotentialTable::Vector table1( 2 );
      table1[ 0 ] = 0.4;
      table1[ 1 ] = 0.6;

      PotentialTable p1( table1, domain1, multiplicity1 );

      // create p(A|B)=( 0.8, 0.2 )
      //               ( 0.3, 0.7 )
      PotentialTable::VectorI domain2( 2 );
      domain2[ 0 ] = 0;
      domain2[ 1 ] = 1;
      PotentialTable::VectorI multiplicity2( 2 );
      multiplicity2[ 0 ] = 2;
      multiplicity2[ 1 ] = 2;

      PotentialTable::Vector table2( 4 );
      table2[ 0 ] = 0.8;
      table2[ 1 ] = 0.2;
      table2[ 2 ] = 0.3;
      table2[ 3 ] = 0.7;

      PotentialTable p2( table2, domain2, multiplicity2 );


      // now compute P(A,B) = P(A|B)P(B)
      // expected: | p(a=0, b=0)p(b = 0 ) ; p(a=1, b=0)p(b = 0 ) |
      //           | p(a=0, b=1)p(b = 1 ) ; p(a=1, b=1)p(b = 1 ) |
      PotentialTable pjoint = p1 * p2;
      pjoint.print( std::cout );

      TESTER_ASSERT( core::equal( pjoint.getTable()[ 0 ], table2[ 0 ] * table1[ 0 ] ) );
      TESTER_ASSERT( core::equal( pjoint.getTable()[ 1 ], table2[ 1 ] * table1[ 0 ] ) );
      TESTER_ASSERT( core::equal( pjoint.getTable()[ 2 ], table2[ 2 ] * table1[ 1 ] ) );
      TESTER_ASSERT( core::equal( pjoint.getTable()[ 3 ], table2[ 3 ] * table1[ 1 ] ) );
   }

   void testMarginalization1()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 1;

      PotentialTable p2 = p1.marginalization( var );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      TESTER_ASSERT( p2.getTable()[ 0 ] == 0.33 );
      TESTER_ASSERT( p2.getTable()[ 1 ] == 0.51 );
      TESTER_ASSERT( p2.getTable()[ 2 ] == 0.05 );
      TESTER_ASSERT( p2.getTable()[ 3 ] == 0.07 );
      TESTER_ASSERT( p2.getTable()[ 4 ] == 0.24 );
      TESTER_ASSERT( p2.getTable()[ 5 ] == 0.39 );
   }

   void testMarginalization2()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 0;

      PotentialTable p2 = p1.marginalization( var );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      TESTER_ASSERT( core::equal( p2.getTable()[ 0 ], 0.6, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 1 ], 0.24, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 2 ], 0.12, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 3 ], 0.0, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 4 ], 0.36, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 5 ], 0.27, 1e-3 ) );
   }

   void testMarginalization3()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 2;

      PotentialTable p2 = p1.marginalization( var );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 4 );
      TESTER_ASSERT( core::equal( p2.getTable()[ 0 ], 0.45, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 1 ], 0.63, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 2 ], 0.17, 1e-3 ) );
      TESTER_ASSERT( core::equal( p2.getTable()[ 3 ], 0.34, 1e-3 ) );
   }

   void testConditioning1a()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      //const double pevidence = 0.25 + 0.08 + 0.05 + 0.15 + 0.09;
      const double pevidence = 1; // there is no normalization anymore!

      double vals2[] =
      {
         0.25 / pevidence,
         0.08 / pevidence,
         0.05 / pevidence,
         0    / pevidence,
         0.15 / pevidence,
         0.09 / pevidence
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 0;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 0;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning1b()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; //0.35 + 0.16 + 0.07 + 0 + 0.21 + 0.18;

      double vals2[] =
      {
         0.35 / pevidence,
         0.16 / pevidence,
         0.07 / pevidence,
         0    / pevidence,
         0.21 / pevidence,
         0.18 / pevidence
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 1;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 0;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning2a()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; //0.25 + 0.35 + 0.05 + 0.07 + 0.15 + 0.21;

      double vals2[] =
      {
         0.25 / pevidence,
         0.35 / pevidence,
         0.05 / pevidence,
         0.07    / pevidence,
         0.15 / pevidence,
         0.21 / pevidence
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 0;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 1;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning2b()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; //0.08 + 0.16 + 0 + 0 + 0.09 + 0.18;

      double vals2[] =
      {
         0.08 / pevidence,
         0.16 / pevidence,
         0.00 / pevidence,
         0.00 / pevidence,
         0.09 / pevidence,
         0.18 / pevidence
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 1;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 1;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 6 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning3a()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; //0.25 + 0.35 + 0.08 + 0.16;

      double vals2[] =
      {
         0.25 / pevidence,
         0.35 / pevidence,
         0.08 / pevidence,
         0.16 / pevidence,
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 0;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 2;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 4 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning3b()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; //0.05 + 0.07 + 0 + 0;

      double vals2[] =
      {
         0.05 / pevidence,
         0.07 / pevidence,
         0.0 / pevidence,
         0.0 / pevidence,
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 1;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 2;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 4 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }

   void testConditioning3c()
   {
      double vals[] =
      {
         0.25, 0.35, 0.08, 0.16, 0.05, 0.07, 0, 0, 0.15, 0.21, 0.09, 0.18
      };

      const double pevidence = 1.0; // 0.15 + 0.21 + 0.09 + 0.18;

      double vals2[] =
      {
         0.15 / pevidence,
         0.21 / pevidence,
         0.09 / pevidence,
         0.18 / pevidence,
      };

      PotentialTable::VectorI domain1( 3 );
      domain1[ 0 ] = 0;
      domain1[ 1 ] = 1;
      domain1[ 2 ] = 2;

      PotentialTable::VectorI multiplicity1( 3 );
      multiplicity1[ 0 ] = 2;
      multiplicity1[ 1 ] = 2;
      multiplicity1[ 2 ] = 3;

      PotentialTable::Vector table( vals, 12, false );
      PotentialTable p1( table, domain1, multiplicity1 );

      PotentialTable::VectorI var( 1 );
      var[ 0 ] = 2;
      PotentialTable::VectorI index( 1 );
      index[ 0 ] = 2;

      PotentialTable p2 = p1.conditioning( var, index );
      p2.print( std::cout );

      TESTER_ASSERT( p2.getTable().size() == 4 );
      for ( size_t n = 0; n < p2.getTable().size(); ++n )
      {
         TESTER_ASSERT( core::equal( p2.getTable()[ n ], vals2[ n ], 1e-3 ) );
      }
   }
};


#ifndef DONT_RUN_TEST
TESTER_TEST_SUITE(TestPotentialTable);
TESTER_TEST(testMul1);
TESTER_TEST(testMul2);
TESTER_TEST(testMul3);
TESTER_TEST(testMul4);
TESTER_TEST(testMul5);
TESTER_TEST(testMarginalization1);
TESTER_TEST(testMarginalization2);
TESTER_TEST(testMarginalization3);
TESTER_TEST(testConditioning1a);
TESTER_TEST(testConditioning1b);
TESTER_TEST(testConditioning2a);
TESTER_TEST(testConditioning2b);
TESTER_TEST(testConditioning3a);
TESTER_TEST(testConditioning3b);
TESTER_TEST(testConditioning3c);
TESTER_TEST_SUITE_END();
#endif%