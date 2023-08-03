#include <math.h>
#include <time.h>

#define PI 3.14159265

template <class anyNode>
void fillGraph(anyNode* nodeList[], int n_nodes, int max_x, int max_y, int min_neighbors, int max_neighbors)
{
    srand(time(NULL));
    float x;
    float y;
    for (int i = 0; i < n_nodes; ++i)
    {
        x = rand() % max_x;
        y = rand() % max_y;
        nodeList[i] = new anyNode(x, y);
    }

    for (int i = 0; i < n_nodes; ++i)
    {
        int n_neighbors = min_neighbors + rand() % (max_neighbors - min_neighbors);
        for (int j = 0; j < n_neighbors; ++j)
        {
            int neighbor_index = rand() % n_nodes;
            if (neighbor_index == i)
            {
                j--;
                continue;
            }
            nodeList[i]->addNeighbor(nodeList[neighbor_index]);
        }
    }
}

template <class anyNode>
void fillGraphGrid(anyNode* nodeList[], int space, int gridWidth, int gridHeight)
{
    srand(time(NULL));

    for (int i = 0; i < gridWidth; ++i)
        for (int j = 0; j < gridHeight; ++j)
        {
            // add space/2 for padding
            int x = space/2 + (i * space);
            int y = space/2 + (j * space);
            nodeList[i + j * gridWidth] = new anyNode(x, y);
        }

    for (int i = 0; i < gridWidth; ++i)
        for (int j = 0; j < gridHeight; ++j)
        {
            float rnd;
            if (i > 0)
            {
                rnd = float(rand()) / RAND_MAX;
                if (rnd < 0.70)
                    nodeList[i + j * gridWidth]->addNeighbor(nodeList[i-1 + j * gridWidth]);
            }
            if (j > 0)
            {
                rnd = float(rand()) / RAND_MAX;
                if (rnd < 0.70)
                    nodeList[i + j * gridWidth]->addNeighbor(nodeList[i + (j-1) * gridWidth]);
            }
            if (i > 0 && j > 0)
            {
                rnd = float(rand()) / RAND_MAX;
                if (rnd < 0.60)
                    nodeList[i + j * gridWidth]->addNeighbor(nodeList[i-1 + (j-1) * gridWidth]);
            }
        }
}

template <class anyNode>
void graphInfo(anyNode* nodeList[], int n_nodes)
{
    for (int i = 0; i < n_nodes; ++i)
    {
        std::cout << "Node " << nodeList[i] << std::endl;
        std::cout << "  Coordinate: (" << nodeList[i]->x() << ", " << nodeList[i]->y() << ")" << std::endl;
        std::cout << "  Neighbors: " << std::endl;
        for (anyNode* neighbor: nodeList[i]->neighbors())
            std::cout << "  - " << neighbor << " - Distance: " << nodeList[i]->distance(neighbor) << std::endl;
    }
}

sf::RectangleShape Line(float x1, float y1, float x2, float y2, float thickness = 1)
{
    sf::RectangleShape line;
    float len, angle;

    line.setPosition(x1, y1);
    len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    angle = atan((y2 - y1) / (x2 - x1)) * 180/PI;
    // line pointing down-left and top-left must be incremented by 180 deg
    if (x2 - x1 < 0) angle += 180;

    line.setSize(sf::Vector2f(len, thickness));
    line.setFillColor(sf::Color(100, 100, 100));
    line.setRotation(angle);
    return line;
}
