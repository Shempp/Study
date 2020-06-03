'use strict';

// Define the `rentalpropertyApp` module
// TODO: add bound forms support for AngularJS ('djng.forms')?
var rentalpropertyApp = angular.module('rentalpropertyApp', [
    'rentingItemsList',
    'ngRoute',
    'rentingItemDetail'
    //'djng.forms'
]);

// As a convention in web applications, Ajax requests shall send the HTTP-Header (X-Requested-With: XMLHttpRequest)
rentalpropertyApp.config(function($httpProvider) {
    $httpProvider.defaults.headers.common['X-Requested-With'] = 'XMLHttpRequest';
});