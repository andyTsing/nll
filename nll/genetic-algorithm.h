/*
 * Numerical learning library
 * http://nll.googlecode.com/
 *
 * Copyright (c) 2009-2012, Ludovic Sibille
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Ludovic Sibille nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY LUDOVIC SIBILLE ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NLL_GENETIC_ALGORITHM_H_
# define NLL_GENETIC_ALGORITHM_H_

# include <assert.h>
# include <vector>
# include <algorithm>
# include <iostream>

# pragma warning( push )
# pragma warning( disable:4800 ) // forcing unsigned long to bool

namespace nll
{
namespace algorithm
{
   /**
    @ingroup algorithm
    @brief Define when a genetic algorithm should stop. Here after a fixed number of iterations
    */
   template <class Gene>
   class GeneticAlgorithmStopMaxIteration
   {
   public:
      typedef std::vector<Gene>     Genes;

   public:
      GeneticAlgorithmStopMaxIteration( const size_t maxIteration ) : _maxIteration( maxIteration ), _iter( 0 ){}
      bool operator()( const Genes& ) const
      {
         if ( !_iter++ )
            return true;
         return ( _iter ) % ( _maxIteration + 1 );
      }

   private:
      mutable size_t _iter;
      size_t _maxIteration;
   };

   /**
    @ingroup algorithm
    @brief mutate a gene. Randomly change one of its bit.
    
    It is done at BIT LEVEL: only Gene with plain data could be used with this class
    */
   template <class Gene>
   class GeneticAlgorithmMutateBit
   {
   public:
      void operator()( Gene& mutate ) const
      {
         size_t s	= sizeof (Gene);
         ui8  n	= rand() % 8;
         size_t ss	= rand() % s;
         ui8	 nb = 1 << n;
         char* p = (char*)(&mutate);
         p[ss] = p[ss] ^ nb;
      }
   };


   /**
    @ingroup algorithm
    @brief mutate a gene. Supposing the gene could be seen as an array.

    Gene needs these operations to be implemented:
     - operator[]
     - operator+
     - size()
    */
   template <class Gene>
   class GeneticAlgorithmMutateArray
   {
   public:
      void operator()( Gene& mutate ) const
      {
         size_t g = rand() % mutate.size();
         mutate[ g ] = mutate[ g ] + ( rand() % 3 ) - 2;
      }
   };

   /**
    @ingroup algorithm
    @brief Select genes using roulette wheel algorithm and elitism
           (the best gene is always selected and never mutated)
    */
   template <class Gene, class GeneEvaluator>
   class GeneticAlgorithmSelectElitism
   {
   public:
      typedef std::vector<Gene>     Genes;

   protected:
      GeneticAlgorithmSelectElitism& operator=( const GeneticAlgorithmSelectElitism );

   public:
      GeneticAlgorithmSelectElitism( const GeneEvaluator& evaluator, bool printEvaluation = true ) : _evaluator( evaluator ), _printEvaluation( printEvaluation ){}
      Genes operator()( const Genes& genes, size_t nbGenesToSelect ) const
	   {
		   typedef std::pair<f64, size_t>	Pair;
		   typedef std::vector<Pair>		Pairs;

		   Genes newGenes;
		   Pairs pairs;

		   for ( size_t n = 0; n < genes.size(); ++n )
		   {
			   clock_t t = clock();
            double val = _evaluator( genes[ n ] );
			   pairs.push_back( Pair( 1 / val, n ) );
			   if ( _printEvaluation )
            {
               std::stringstream ss;
               for ( size_t nn = 0; nn < genes[ n ].size(); ++nn )
                  ss << " " << genes[ n ][ nn ];
               core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, "eval=" + core::val2str( n ) + " time=" + core::val2str( ( f32 )( clock() - t ) / CLOCKS_PER_SEC) + " val=" + core::val2str( 1 / pairs.rbegin()->first ) + ss.str() );
            }
		   }
		   std::sort( pairs.rbegin(), pairs.rend() );
		   Pairs::const_iterator it = pairs.begin();
   		
		   if ( _printEvaluation )
         {
            std::stringstream ss;
            ss << "best = " << 1 / it->first;
            for ( size_t n = 0; n < genes[ it->second ].size(); ++n )
               ss << " " << genes[ it->second ][ n ];
            ss << std::endl;
            core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, ss.str() );
         }
   		
         // copy from begin to nb genes
         assert( pairs.size() );
		   for ( size_t n = 0; n < ( nbGenesToSelect ) && n < genes.size(); ++n, ++it )
			   newGenes.push_back( genes[ it->second ] );
		   return newGenes;
      }

   private:
      const GeneEvaluator& _evaluator;
      bool                 _printEvaluation;
   };

   /**
    @ingroup algorithm
    @brief recombinate a gene using 2 splits. part between these splits are swapped.

    need Gene(const size&)
    */
   template <class Gene>
   class GeneticAlgorithmRecombinate2Splits
   {
   public:
      Gene operator()( const Gene& g1, const Gene& g2, size_t size ) const
      {
         size_t r1 = rand() % size;
	      size_t r2 = rand() % size;
	      if ( r1 > r2 )
		      std::swap( r1, r2 );
	      Gene g( size );
         for ( size_t n = 0; n < r1; ++n )
            g[ n ] = g1[ n ];
	      for ( size_t n = r1; n <= r2; ++n )
		      g[ n ] = g2[ n ];
         for ( size_t n = r2 + 1; n < size; ++n )
		      g[ n ] = g1[ n ];
	      return g;
      }
   };

   /**
    @ingroup algorithm
    @brief Highly customizable genetic algorithm. The cost function will be <b>maximized</b>.
    
    All operations are implemented by the template parameters.
    Need Gene.size().
   */
   template < class Gene,
              class GeneGenerate,
              class GeneEvaluator,
              class GeneticAlgorithmSelect               = GeneticAlgorithmSelectElitism<Gene, GeneEvaluator>,
              class GeneticAlgorithmStop                 = GeneticAlgorithmStopMaxIteration<Gene>,
              class GeneticAlgorithmRecombinate          = GeneticAlgorithmRecombinate2Splits<Gene>,
              class GeneticAlgorithmMutate               = GeneticAlgorithmMutateArray<Gene>
            >
   class GeneticAlgorithm
   {
      typedef std::vector<Gene> Genes;

   public:
      GeneticAlgorithm( 
                        const GeneGenerate&                       generator,
                        const GeneEvaluator&                      evaluator,
                        GeneticAlgorithmSelect&                   select,
                        const GeneticAlgorithmStop&               stop,
                        const GeneticAlgorithmRecombinate&        recombinate,
                        const GeneticAlgorithmMutate&             mutate
                        ) : _generator( generator ), _evaluator( evaluator ), _stop( stop ), _recombinate( recombinate ), _select( select ), _mutate( mutate )
      {}

      Genes optimize( size_t populationSize,
                      double mutationRate,
                      double selectionRate,
                      size_t nbRounds,
                      const Gene seed = GeneGenerate() )
      {
         Genes genes;
         genes.push_back( seed );
         for ( size_t n = 0; n < populationSize; ++n )
			   genes.push_back( _generator() );
         size_t round = 0;
         core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, "Genetic Algorithm New Instance (remaining=" + core::val2str( nbRounds ) + ")" );
         while ( _stop( genes ) )
         {
            core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, "round=" + core::val2str( round ) );
            Genes newBreed = _select( genes, static_cast<size_t>( selectionRate * populationSize ) );
            size_t size = static_cast<size_t>( newBreed.size() );
            ensure( newBreed.size(), "error: bad proportion" );
            while (newBreed.size() < populationSize)
			   {
				   size_t n1 = static_cast<size_t>( rand() % size );
				   size_t n2 = static_cast<size_t>( rand() % size );
				   newBreed.push_back( _recombinate( newBreed[ n1 ], newBreed[ n2 ], seed.size() ) );
			   }
            for (size_t i = 2; i < newBreed.size(); ++i)
			   {
				   f32 n = (f32)(rand() % 1000);
				   if (n <= mutationRate * 1000)
					   _mutate( newBreed[ i ] );
			   }
			   genes = newBreed;
            ++round;
         }
         if ( nbRounds > 1 )
            return optimize( populationSize, mutationRate, selectionRate, nbRounds - 1, genes[ 0 ] );
         else
            return genes;
      }

   private:
      GeneticAlgorithm& operator=( const GeneticAlgorithm& );

   private:
      const GeneGenerate&                        _generator;
      const GeneEvaluator&                       _evaluator;
      const GeneticAlgorithmStop&                _stop;
      const GeneticAlgorithmRecombinate&         _recombinate;
      GeneticAlgorithmSelect                      _select;
      const GeneticAlgorithmMutate&              _mutate;
   };

    /**
     @ingroup algorithm
     @brief Helper function to create and run genetic algorithms
    */
   template < class Gene,
              class GeneGenerate,
              class GeneEvaluator,
              class GeneticAlgorithmSelect,
              class GeneticAlgorithmStop,
              class GeneticAlgorithmRecombinate,
              class GeneticAlgorithmMutate
            >
   std::vector<Gene> launchGeneticAlgorithm(
                                             const Gene&                         seed,
                                             GeneGenerate&                       generator,
                                             GeneEvaluator&                      evaluator,
                                             GeneticAlgorithmSelect&             select,
                                             GeneticAlgorithmStop&               stop,
                                             GeneticAlgorithmRecombinate&        recombinate,
                                             GeneticAlgorithmMutate&             mutate,
                                             size_t                                populationSize = 100,
                                             f64                                 mutationRate   = 0.3,
                                             f64                                 selectionRate  = 0.5,
                                             size_t                                nbRounds       = 1
                                           )
  {
     GeneticAlgorithm<Gene, GeneGenerate, GeneEvaluator, GeneticAlgorithmSelect, GeneticAlgorithmStop, GeneticAlgorithmRecombinate, GeneticAlgorithmMutate> geneticAlgorithm( generator, evaluator, select, stop, recombinate, mutate );
     return geneticAlgorithm.optimize( populationSize, mutationRate, selectionRate, nbRounds, seed );
  }

  /**
   @ingroup algorithm
   @brief Helper function to create and run genetic algorithms
  */
  template <  class Gene,
              class GeneGenerate,
              class GeneEvaluator,
              class GeneMutate
           >
   std::vector<Gene> launchGeneticAlgorithm(
                                             const Gene&                         seed,
                                             GeneGenerate&                       generator,
                                             GeneEvaluator&                      evaluator,
                                             GeneMutate&                         mutator,
                                             size_t                                nbCycle,
                                             size_t                                populationSize = 100,
                                             f64                                 mutationRate   = 0.3,
                                             f64                                 selectionRate  = 0.5,
                                             size_t                                nbRounds       = 1
                                           )
  {
      GeneticAlgorithmSelectElitism<Gene, GeneEvaluator> selector( evaluator, true );
      GeneticAlgorithmStopMaxIteration<Gene>             stop( nbCycle );
      GeneticAlgorithmRecombinate2Splits<Gene>           recombinate;
      return launchGeneticAlgorithm( seed, generator, evaluator, selector, stop, recombinate, mutator, populationSize, mutationRate, selectionRate, nbRounds );
  }

  /**
   @ingroup algorithm
   @brief Helper function to create and run genetic algorithms
  */
  template <  class Gene,
              class GeneGenerate,
              class GeneEvaluator
           >
   std::vector<Gene> launchGeneticAlgorithm(
                                             const Gene&                         seed,
                                             GeneGenerate&                       generator,
                                             GeneEvaluator&                      evaluator,
                                             size_t                                nbCycle,
                                             size_t                                populationSize = 100,
                                             f64                                 mutationRate   = 0.3,
                                             f64                                 selectionRate  = 0.5,
                                             size_t                                nbRounds       = 1
                                           )
  {
      GeneticAlgorithmSelectElitism<Gene, GeneEvaluator> selector( evaluator, true );
      GeneticAlgorithmStopMaxIteration<Gene>             stop( nbCycle );
      GeneticAlgorithmRecombinate2Splits<Gene>           recombinate;
      GeneticAlgorithmMutateArray<Gene>                  mutate;
      return launchGeneticAlgorithm( seed, generator, evaluator, selector, stop, recombinate, mutate, populationSize, mutationRate, selectionRate, nbRounds );
  }
}
}
 
# pragma warning( pop )

#endif
