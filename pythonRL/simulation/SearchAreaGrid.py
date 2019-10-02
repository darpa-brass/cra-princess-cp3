import math

from simulation.Point import Point


class SearchAreaGrid(object):
    def __init__(self, p1, p2, cell_size):
        grid_x_len = math.fabs(p2.x - p1.x)
        grid_y_len = math.fabs(p2.y - p1.y)
        self.min_x = p1.x
        self.min_y = p1.y
        self.max_x = p2.x
        self.max_y = p2.y
        self.cell_size = cell_size
        self.num_cells_x = int(math.ceil(grid_x_len / cell_size))
        self.num_cells_y = int(math.ceil(grid_y_len / cell_size))
        # noinspection PyUnusedLocal
        self.grid = [[False for i in range(0, self.num_cells_y)] for j in range(0, self.num_cells_x)]
        self.num_visited = 0

    def visit(self, p):
        half_view = self.cell_size / 2.0
        point_to_visit = Point(p.x, p.y)
        left_point = Point(p.x - half_view, p.y)
        right_point = Point(p.x + half_view, p.y)
        up_point = Point(p.x, p.y + half_view)
        down_point = Point(p.x, p.y - half_view)
        left_up_point = Point(p.x - half_view, p.y + half_view)
        left_down_point = Point(p.x - half_view, p.y - half_view)
        right_up_point = Point(p.x + half_view, p.y + half_view)
        right_down_point = Point(p.x + half_view, p.y - half_view)
        self.visit_helper(point_to_visit, half_view)
        self.visit_helper(left_point, half_view)
        self.visit_helper(right_point, half_view)
        self.visit_helper(up_point, half_view)
        self.visit_helper(down_point, half_view)
        self.visit_helper(left_up_point, half_view)
        self.visit_helper(left_down_point, half_view)
        self.visit_helper(right_up_point, half_view)
        self.visit_helper(right_down_point, half_view)

    def visit_helper(self, p, half_view):
        point_to_visit = Point(p.x, p.y)
        if not self.in_search_area(p):
            if math.fabs(p.x - self.min_x) <= half_view:
                point_to_visit = Point(self.min_x, point_to_visit.y)
            if math.fabs(p.x - self.max_x) <= half_view:
                point_to_visit = Point(self.max_x, point_to_visit.y)
            if math.fabs(p.y - self.min_y) <= half_view:
                point_to_visit = Point(point_to_visit.x, self.min_y)
            if math.fabs(p.y - self.max_y) <= half_view:
                point_to_visit = Point(point_to_visit.x, self.max_y)
        # central point
        index_x = int(math.floor((point_to_visit.x - self.min_x) / self.cell_size))
        index_y = int(math.floor((point_to_visit.y - self.min_x) / self.cell_size))
        if self.num_cells_x > index_x >= 0 and self.num_cells_y > index_y >= 0:
            if not self.grid[index_x][index_y]:
                self.grid[index_x][index_y] = True
                self.num_visited += 1

    def get_coverage(self):
        num_cells = self.num_cells_x * self.num_cells_y
        return float(self.num_visited) / float(num_cells)

    def in_search_area(self, p):
        return not (
                p.x < self.min_x or p.x > self.max_x or
                p.y < self.min_y or p.y > self.max_y)
