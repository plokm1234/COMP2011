void temperature::set(temperature* this, double d, char s)
{
    switch (s)
    {
        case KELVIN: this->degree = d; break;
        case CELSIUS: this->degree = d + 273.15; break;
        ...
    }
    ...
}
