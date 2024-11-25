# ContiguousArtGallery

## Degeneracies
Right now, visibility polygons are calculated in a regularized manner ignoring 'needles' (see https://doc.cgal.org/latest/Visibility_2/index.html#Chapter_2D_Visibility_Computation).
This will for some specific instances cause the feasible regions to be smaller than they should be, thus potentially causing non-maximal greedy steps.

(We believe as long as no three points of the input are collinear, this should not be a problem.)
