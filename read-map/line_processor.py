import cv2


def drawCircle(img, x, y, cell_side_len):
    height, width = img.shape[:2]
    if x < 0 or x >= width or y < 0 or y >= height:
        return -1, -1
    x, y = int(x), int(y)
    cv2.circle(img, (x, y), 10, (255, 255, 0))

    x_index = x // cell_side_len
    y_index = y // cell_side_len

    cv2.imshow("ee", img)
    # cv2.waitKey(0)
    return x_index, y_index


def line_process(lines, maze_x_max, maze_y_max, img):
    cell_side_len = (maze_x_max + maze_y_max) / 2 / 10

    for line in lines:
        line = line[0]
        # 预处理，去除不符合要求的线段
        length_threshold = cell_side_len / 2
        if abs(line[0] - line[2]) + abs(line[1] - line[3]) < length_threshold:  # 长度过短
            continue
        # 这里还需要判断一下边界上的线段

        # 判断方向
        line_direction = False  # false为横向，true为纵向
        approximate = 5
        if abs(line[0] - line[2]) < approximate:    # x坐标大致一致，则为y方向，纵向
            line_direction = True
        elif abs(line[1] - line[3]) < approximate:
            line_direction = False
        else:
            continue    # x和y坐标差别都较大，不是迷宫墙壁，跳过

        if line_direction:  # 纵向，x几乎一致，有差距
            # 判断跨越了几个cell
            x1, y1, x2, y2 = map(int, line)
            cv2.line(img, (x1, y1), (x2, y2), (0, 0, 255), 2)

            line_len = abs(y2 - y1)
            num_of_cells = line_len / cell_side_len
            # print(num_of_cells)
            num_of_cells = round(num_of_cells)
            # print(num_of_cells)

            # show circle on the line
            for i in range(int(num_of_cells)):
                point_y = int(min(y2, y1) + cell_side_len / 2 + i * cell_side_len)
                output = [drawCircle(img, x1 - cell_side_len / 2, point_y, cell_side_len),
                          drawCircle(img, x1 + cell_side_len / 2, point_y, cell_side_len)]
                output = list(map(lambda x: (int(x[0]), int(x[1])), output))

                if (-1, -1) not in output:
                    for elem in output:
                        print(elem[0], elem[1], " ", end="")
                    print("")
        else:
            # 判断跨越了几个cell
            x1, y1, x2, y2 = map(int, line)
            cv2.line(img, (x1, y1), (x2, y2), (0, 0, 255), 2)

            line_len = abs(x2 - x1)
            num_of_cells = line_len / cell_side_len
            # print(num_of_cells)
            num_of_cells = round(num_of_cells)
            # print(num_of_cells)

            # show circle on the line
            for i in range(int(num_of_cells)):
                point_x = int(min(x2, x1) + cell_side_len / 2 + i * cell_side_len)
                output = [drawCircle(img, point_x, y1 - cell_side_len / 2, cell_side_len),
                          drawCircle(img, point_x, y1 + cell_side_len / 2, cell_side_len)]
                output = list(map(lambda x: (int(x[0]), int(x[1])), output))

                if (-1, -1) not in output:
                    for elem in output:
                        print(elem[0], elem[1], " ", end="")
                    print("")


