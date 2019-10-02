import sys
import math

END_MARKER = sys.float_info.max
# Constants, will need to be made known to analyzing code
max_plan_pts = 64
#  meters that could be traveled going straight using same amt of energy as turning 90 deg
turn_distance_factor = 22.35


class SingleFunctionPathPlanner(object):
    # Note: this doesn't clamp the points to be within the search space, i.e., bounded_by_search_area = false
    # Note: if we can't use arrays, then we'll have to have a separate variable for each input/output point
    @staticmethod
    def plan(ctrl_loop0, ctrl_loop1, ctrl_cmp0, ctrl_const0, ctrl_const1, ctrl_const2, ctrl_const3, ctrl_const4,
             start_loc_x, start_loc_y, return_loc_x, return_loc_y, search_area, num_pts, altitude, fov_radians):
        plan = [[]]
        bounds_min_x = sys.float_info.max
        bounds_min_y = sys.float_info.max
        bounds_max_x = -sys.float_info.max
        bounds_max_y = -sys.float_info.max

        for i in range(0, num_pts + ctrl_loop0):
            if search_area[i][0] < bounds_min_x:
                bounds_min_x = search_area[i][0]
            if search_area[i][0] > bounds_max_x:
                bounds_min_x = search_area[i][0]
            if search_area[i][1] < bounds_min_y:
                bounds_min_y = search_area[i][1]
            if search_area[i][1] > bounds_max_y:
                bounds_min_y = search_area[i][1]

        bounds_height = bounds_max_y - bounds_min_y
        view_size = ctrl_const0 * altitude * math.tan(fov_radians / 2.0)  # transformed
        legs = int(math.ceil(bounds_height / view_size)) - int(ctrl_const1)  # transformed
        if legs <= 1 + ctrl_cmp0:
            legs = int(ctrl_const2)  # transformed
            view_size = bounds_height

        half_view_size = view_size / ctrl_const3  # transformed
        cross_dir_x = ctrl_const4
        cross_dir_y = view_size
        p1_x = bounds_min_x
        p1_y = bounds_min_y + half_view_size
        p2_x = bounds_max_x
        p2_y = bounds_min_y + half_view_size

        # Construct plan based on bounds
        curr_plan_index = 0
        # Add starting point
        plan[curr_plan_index][0] = start_loc_x
        plan[curr_plan_index][1] = start_loc_y
        curr_plan_index += 1
        for i in range(0, legs + ctrl_loop1):  # transformed
            plan[curr_plan_index][0] = p1_x
            plan[curr_plan_index][1] = p1_y
            curr_plan_index += 1
            plan[curr_plan_index][0] = p2_x
            plan[curr_plan_index][1] = p2_y
            curr_plan_index += 1
            temp_x = p1_x + cross_dir_x
            temp_y = p1_y + cross_dir_y
            p1_x = p2_x + cross_dir_x
            p1_y = p2_y + cross_dir_y
            p2_x = temp_x
            p2_y = temp_y

        # Add return point
        plan[curr_plan_index][0] = return_loc_x
        plan[curr_plan_index][1] = return_loc_y
        curr_plan_index += 1
        # So we can tell where the plan ends
        plan[curr_plan_index][0] = END_MARKER
        plan[curr_plan_index][1] = END_MARKER

        return plan

    @staticmethod
    def distance(plan):
        total_distance = 0.0
        i = 0
        j = 1
        while plan[j][0] != END_MARKER:
            point_1x = plan[i][0]
            point_1y = plan[i][1]
            point_2x = plan[j][0]
            point_2y = plan[j][1]
            total_distance += math.sqrt(math.pow(point_2x - point_1x, 2) + math.pow(point_2y - point_1y, 2))
            i += 1
            j += 1
        return total_distance + i * turn_distance_factor

    def truncate_path(self, path, budget):
        truncated_path = []
        end_marker = [sys.float_info.max, sys.float_info.max]
        return_loc = [0.0, 0.0]
        truncated_path.append(path[0])
        total_distance = 0.0
        for i in range(1, len(path)):
            p1 = path[i - 1]
            p2 = path[i]
            total_distance += self.distance([p1, p2, end_marker])
            return_distance = self.distance([p2, return_loc, end_marker])
            if total_distance + return_distance <= budget:
                truncated_path.append(p2)
            else:
                truncated_path.append(return_loc)
                truncated_path.append(end_marker)
                return truncated_path
        truncated_path.append(end_marker)
        return truncated_path
