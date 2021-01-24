import constants


class Gravity:
    def __init__(self, altitude):
        self.altitude = altitude

    def gravity(self, planet='earth'):
        """return acceleration due to gravity density wrt altitude."""
        if planet == 'earth':
            r_0 = constants.radius_earth()
            m = constants.mass_earth()
        elif planet == 'jupiter':
            r_0 = constants.radius_jupiter()
            m = constants.mass_jupiter()
        elif planet == 'mars':
            r_0 = constants.radius_mars()
            m = constants.mass_mars()
        elif planet == 'mercury':
            r_0 = constants.radius_mercury()
            m = constants.mass_mercury()
        elif planet == 'neptune':
            r_0 = constants.radius_neptune()
            m = constants.mass_neptune()
        elif planet == 'saturn':
            r_0 = constants.radius_saturn()
            m = constants.mass_saturn()
        elif planet == 'uranus':
            r_0 = constants.radius_uranus()
            m = constants.mass_uranus()
        elif planet == 'venus':
            r_0 = constants.radius_venus()
            m = constants.mass_venus()

        r = r_0 + self.altitude / constants.m2ft()
        g = constants.m2ft() * constants.gravitational_constant() * m / r ** 2
        return g

# Public Methods #######################################################################################################
