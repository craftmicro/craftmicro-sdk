# Generate numbers to graph pixel coverage

import math

debug = True

rdeg = [-60]

for deg in rdeg:

    if debug:
        xr = [0]
        yr = [0.5]
    else:
        xr = [i * 0.05 for i in range(0, 21)]
        yr = [i * 0.05 for i in range(0, 21)]

    print('deg {0}'.format(deg))
    if not debug:
        for x in xr:
            print(', {0:.4f}'.format(x), end='')
        print()

    for y in yr:
        if debug:
            print('y={0:.4f}: '.format(y), end='')
        else:
            print('{0:.4f}'.format(y), end=', ')
        for x in xr:

            cos = math.cos(math.radians(deg))
            sin = math.sin(math.radians(deg))
            if cos == 0:
                m = 0
            else:
                m = sin/cos
            if debug: print('  m {0:.2f}'.format(m))

            xx = y * m
            yy = x * m

            ### top left
            b = x * y
            if debug: print('  start with {0:.2f}'.format(b))

            xc = x - xx #x-crossing
            yc = y + yy #y-crossing
            if debug: print('  xx {0:.2f} yy {1:.2f}'.format(xx, yy))
                
            c = (xx * y * 0.5)
            b = b - c
            if debug: print('  xc {0:.2f}. + {1:.4f}'.format(xc, -c), end='')
            if xc < 0:
                c = xc * (xc/m) * 0.5
                b = b + c
                if debug: print(' - {0:.4f} (cx < 0)'.format(-c), end='')
            elif xc > 1:
                c = (1-xc) * ((1-xc)/m) * 0.5
                b = b + c
                if debug: print(' - {0:.4f} (xc > 1)'.format(-c), end='')
            if debug: print('. b is now {0:.4f}'.format(b))

            c = (yy * x * 0.5)
            b = b + c
            if debug: print('  yc {0:.2f}. - {1:.4f}'.format(yc, -c), end='')
            if yc < 0:
                c = yc * (yc/m) * 0.5
                b = b - c
                if debug: print(' + {0:.4f} (yc < 0)'.format(-c), end='')
            elif yc > 1:
                c = (1-yc) * ((1-yc)/m) * 0.5
                b = b - c
                if debug: print(' + {0:.4f} (yc > 0)'.format(-c), end='')
            if debug: print('')

            if debug:
                print('{0:.4f}'.format(b))
                continue

            if x < 1:
                print('{0:.4f}'.format(b), end=', ')
            else:
                print('{0:.4f}'.format(b))

    print()