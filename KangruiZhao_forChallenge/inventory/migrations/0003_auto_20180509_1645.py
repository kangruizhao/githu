# Generated by Django 2.0.5 on 2018-05-09 21:45

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('inventory', '0002_auto_20180509_1542'),
    ]

    operations = [
        migrations.RenameField(
            model_name='drink',
            old_name='name_drink',
            new_name='name',
        ),
        migrations.RenameField(
            model_name='snack',
            old_name='name_snack',
            new_name='name',
        ),
    ]
