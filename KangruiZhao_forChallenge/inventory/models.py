from django.db import models

# Create your models here.
class Drink(models.Model):
    sname=models.CharField(max_length=200)
    ingredients= models.CharField(max_length=200)
    def __str__(self):
        return self.sname
    def to_class_name(self):
        return self.__class__.__name__


class Snack(models.Model):
    sname=models.CharField(max_length=200)
    ingredients= models.CharField(max_length=200)
    recommended_drink=models.ManyToManyField(Drink)
    def __str__(self):
        return self.sname
    def to_class_name(self):
        return self.__class__.__name__
