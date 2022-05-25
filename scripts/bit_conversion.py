import plotly
import plotly.graph_objs as go

xdata = []
ydata = []
ydata2 = []
b1 = 6
b2 = 2
s = b1-b2
f = ((1<<b1)-1)/((1<<b2)-1)
for i in range(1<<b1):
	j = i >> s
	k = (j << s) | (j >> (b2-s)) if (b2>=s) else (j << s) | (j << (s-b2)) | j
	k2 = int(j*f)
	d = k-k2
	xdata.append(i)
	ydata.append(k)
	ydata2.append(k2)

plotly.offline.plot({
    "data": [go.Scatter(x=xdata, y=ydata, mode='lines', name = 'approx'),go.Scatter(x=xdata, y=ydata2, mode='lines', name = 'actual')],
    "layout": go.Layout(title=str(b1)+'-bits to '+str(b2)+'-bits')
},filename=str(b1)+'-bits_to_'+str(b2)+'-bits.html')
