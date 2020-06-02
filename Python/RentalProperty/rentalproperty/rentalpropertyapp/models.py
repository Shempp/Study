from django.db import models
from django.utils import timezone

# Create your models here.

#PROPERTY_TYPES = [
#    ('TP1', 'Type1'),
#    ('TP2', 'Type2'),
#]

class RentingItem(models.Model):
    price = models.IntegerField()
    address = models.CharField(max_length=256)
    pub_date = models.DateTimeField(default=timezone.now)
    #property_type = models.CharField(max_length=16, choices=PROPERTY_TYPES)

    def __str__(self):
        return self.address