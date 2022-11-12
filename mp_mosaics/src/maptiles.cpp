/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    //myimages -> tile;
    //getRegionColor
    map<Point<3>,TileImage*> color_map;
    vector<Point<3>> points;
    for(auto iter = theTiles.begin(); iter != theTiles.end(); iter++) {
        LUVAPixel ori = iter -> getAverageColor();
        Point<3> ori_p = Point<3>(ori.l,ori.u,ori.v);
        points.push_back(ori_p);
        color_map[ori_p] = &*iter;
    }
    KDTree<3> tree(points);
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    int width = canvas -> getRows();
    int height = canvas -> getColumns();

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            LUVAPixel sour = theSource.getRegionColor(i,j);
            Point<3> sour_p = Point<3>(sour.l,sour.u,sour.v);
            Point<3> find_p = tree.findNearestNeighbor(sour_p);
            canvas -> setTile(i,j, color_map[find_p]);
        }
    }
    

    return canvas;
}

