import constants


class Gravity:
    def __init__(self, altitude):
        self.altitude = altitude

    def gravity(self, planet='earth'):
        """return acceleration due to gravity density wrt altitude."""
        if planet == 'earth':
            r_0 = constants.radius_earth()
            m = constants.mass_earth()
        else:
            r_0 = constants.radius_earth()
            m = constants.mass_earth()

        r = r_0 + self.altitude / constants.m2ft()
        g = constants.m2ft() * constants.gravitational_constant() * m / r ** 2
        return g

# Public Methods #######################################################################################################
