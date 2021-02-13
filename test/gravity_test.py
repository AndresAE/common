from Gravity import Gravity
from test.test_library import is_close

h_0 = Gravity(0)
h_40k = Gravity(40000)

out = list()
out.append((is_close(h_0.gravity(), 32.14894)))
out.append(is_close(h_40k.gravity(), 32.026389))

h_0 = Gravity(0).gravity(planet='mars')
h_40k = Gravity(40000).gravity(planet='mars')

out = list()
out.append((is_close(h_0, 12.17927)))
out.append(is_close(h_40k, 12.09213))

h_0 = Gravity(0).gravity(planet='jupiter')
h_40k = Gravity(40000).gravity(planet='jupiter')

out = list()
out.append((is_close(h_0, 88.82685)))
out.append(is_close(h_40k, 88.79586))

h_0 = Gravity(0).gravity(planet='mercury')
h_40k = Gravity(40000).gravity(planet='mercury')

out = list()
out.append((is_close(h_0, 12.08413)))
out.append(is_close(h_40k, 11.96425))

h_0 = Gravity(0).gravity(planet='moon')
h_40k = Gravity(40000).gravity(planet='moon')

out = list()
out.append((is_close(h_0, 35764733.3800)))
out.append(is_close(h_40k, 97242.73604))

h_0 = Gravity(0).gravity(planet='neptune')
h_40k = Gravity(40000).gravity(planet='neptune')

out = list()
out.append((is_close(h_0, 36.98729)))
out.append(is_close(h_40k, 36.95068))

h_0 = Gravity(0).gravity(planet='saturn')
h_40k = Gravity(40000).gravity(planet='saturn')

out = list()
out.append((is_close(h_0, 36.69637)))
out.append(is_close(h_40k, 36.68101))

h_0 = Gravity(0).gravity(planet='sun')
h_40k = Gravity(40000).gravity(planet='sun')

out = list()
out.append((is_close(h_0, 6024975662.3099)))
out.append(is_close(h_40k, 5513590160.94595))

h_0 = Gravity(0).gravity(planet='uranus')
h_40k = Gravity(40000).gravity(planet='uranus')

out = list()
out.append((is_close(h_0, 29.55228)))
out.append(is_close(h_40k, 29.52389))

h_0 = Gravity(0).gravity(planet='venus')
h_40k = Gravity(40000).gravity(planet='venus')

out = list()
out.append((is_close(h_0, 29.09859)))
out.append(is_close(h_40k, 29.98169))

if any(out):
    print("gravity test passed!")
else:
    print("gravity test failed")
