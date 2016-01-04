#include <QCoreApplication>

// stl library
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>

std::set< std::string > GetSetFromMap( std::multimap< std::string, std::string > rel_map, std::string query_str  ) {

    // Create the output set
    std::set< std::string > output_set;

    // Find the iterators corresponding to the query
    auto rel_it = rel_map.equal_range( query_str );

    // From the iterator create a new set of value
    for (auto it = rel_it.first; it != rel_it.second; ++it)
        output_set.insert( it->second );

    return output_set;
}

std::set< std::string > GetSetFromMap( std::multimap< std::string, std::string > rel_map  ) {

    // Create the output set
    std::set< std::string > output_set;

    // From the iterator create a new set of value
    for (auto it = rel_map.begin(); it != rel_map.end(); ++it)
        output_set.insert( it->second );

    return output_set;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create and initialize the multimap with some colors and associated objects
    const std::multimap< std::string, std::string > relations = { { "Jaune", "Balle de tennis" },
                                                                  { "Jaune", "Citron" },
                                                                  { "Jaune", "Poussin" },
                                                                  { "Orange", "Citrouille" },
                                                                  { "Orange", "Orange" },
                                                                  { "Marron", "Pomme de terre" },
                                                                  { "Marron", "Chocolat" },
                                                                  { "Rouge", "Pomme" },
                                                                  { "Rouge", "Poivron" },
                                                                  { "Rouge", "Tomate" },
                                                                  { "Rouge", "Fraise" },
                                                                  { "Rouge", "Ketchup" },
                                                                  { "Vert", "Pomme" },
                                                                  { "Vert", "Poire" },
                                                                  { "Vert", "Haricot" },
                                                                  { "Vert", "Poivron" },
                                                                  { "Vert", "Geant" } };

    // Create and initialize fruits set
    const std::set< std::string > fruits = { "Citron",
                                             "Orange",
                                             "Pomme",
                                             "Tomate",
                                             "Fraise" };

    // Create and initialize vegetable set
    const std::set< std::string > vegies = { "Citrouille",
                                             "Pomme de terre",
                                             "Pois",
                                             "Haricot",
                                             "Poivron" };

    /* FIND THE GREEN FRUITS */

    // Find a set corresponding to the green objects
    std::set< std::string > rel_set = GetSetFromMap( relations, "Vert" );
    // Make the intersection between the found set and the fruits set
    std::vector< std::string > green_fruits;
    std::set_intersection( rel_set.begin(), rel_set.end(),
                           fruits.begin(), fruits.end(),
                           std::back_inserter( green_fruits ) );
    std::cout << "The green fruits are the following:" << std::endl;
    for( auto it = green_fruits.begin(); it != green_fruits.end(); ++it )
        std::cout << *it << std::endl;

    /* FIND THE RED VEGETABLES */

    // Find a set corresponding to the green objects
    rel_set.clear();
    rel_set = GetSetFromMap( relations, "Rouge" );
    // Make the intersection between the found set and the fruits set
    std::vector< std::string > red_vegies;
    std::set_intersection( rel_set.begin(), rel_set.end(),
                           vegies.begin(), vegies.end(),
                           std::back_inserter( red_vegies ) );
    // Say if there is some red veggie
    std::cout << ( ( red_vegies.size() == 0 ) ? "There is no red vegetables" : "Theres is some red vegetables" ) << std::endl;

    /* FIND THE COLORS OF NEITHER VEGIES OR FRUITS */

    // Compute the union between the vegies and fruits
    std::set< std::string > fruits_vegies( fruits );
    fruits_vegies.insert( vegies.begin(), vegies.end() );

    // Compute a set of the multimap object
    std::set< std::string > rel_set_all = GetSetFromMap( relations );

    // Compute the difference with the multimap
    std::vector< std::string > remaining_objects;
    std::set_difference( rel_set_all.begin(), rel_set_all.end(),
                         fruits_vegies.begin(), fruits_vegies.end(),
                         std::back_inserter(remaining_objects) );

    // Reverse the relations map
    std::multimap< std::string, std::string > rev_key_relations;
    for( auto it = relations.begin(); it != relations.end(); ++it )
        rev_key_relations.insert( std::pair< std::string, std::string >( it->second, it->first) );

    // Store inside a set
    std::set< std::string > color_nor_f_v;
    for( auto it = remaining_objects.begin(); it != remaining_objects.end(); ++it )
        color_nor_f_v.insert( rev_key_relations.find( *it )->second );

    // Show the colors
    std::cout << "The colors of the objects which are neither fruits or vegetables are:" << std::endl;
    for( auto it = color_nor_f_v.begin(); it != color_nor_f_v.end(); ++it )
        std::cout << *it << std::endl;

     /* FIND FRUITS OR VEGIES WITH MULTIPLE COLORS */
    for( auto it = rev_key_relations.begin(); it != rev_key_relations.end(); ++it)
        if( rev_key_relations.count( it->first ) > 1 )
            std::cout << "There is multiple " << it->first << std::endl;

    return a.exec();
}

