from django.db import models

# Create your models here.

#PROPERTY_TYPES = [
#    ('TP1', 'Type1'),
#    ('TP2', 'Type2'),
#]

class RentingItem(models.Model):
    price = models.IntegerField()
    address = models.CharField(max_length=256)
    #property_type = models.CharField(max_length=16, choices=PROPERTY_TYPES)
    def __str__(self):
        return self.price + self.address