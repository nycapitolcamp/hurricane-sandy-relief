#!/usr/bin/env python2

import json
from urllib import urlopen, urlretrieve

from bs4 import BeautifulSoup, SoupStrainer

warming = {'nyc': "http://www.nyc.gov/html/misc/html/2012/warming_ctr.html",
           'nyc_overnight': "http://www.nyc.gov/html/misc/html/2012/overnight_shelter.html",
           'suffolk': "http://scoem.suffolkcountyny.gov/OEM/WarmingCentersOpeninHuntingtonArea.aspx",
           'westchester': "http://www3.westchestergov.com/news/all-press-releases/4373-hurricane-sandy-shelters",
           'nassau': "http://www.nassaucountyny.gov/agencies/CountyExecutive/NewsRelease/2012/11-5-2012.html",
          }

def get_warming_centers_nyc():
    soup = BeautifulSoup(urlopen(warming['nyc']), parse_only=SoupStrainer('table'))
    table = soup.find('table', id='content_table').find('table')

    centers = []
    tr_list = table.find_all('tr', bgcolor=False)

    #tr_list.pop()
    for element in tr_list:
        center = list(element.stripped_strings)
        try:
            open_time, close_time = center[3].split(' - ')
            # assume close_time is pm, but not specified; convert to 24-hour
            close_bits = close_time.split(':')
            close_bits[0] = str(int(close_bits[0]) + 12)
            close_time = ':'.join(close_bits)
        except ValueError:
            open_time, close_time = None, None
        attributes = {'STATE': 'NY', 'SHELTER_NAME': center[0],
                      'ADDRESS': center[1], 'CITY': center[2],
                      'HOURS_OPEN': open_time, 'HOURS_CLOSE': close_time}
        centers.append(dict(attributes=attributes))

    return centers

def get_warming_centers_suffolk():
    soup = BeautifulSoup(urlopen(warming['suffolk']), \
        parse_only=SoupStrainer('div', id='dnn_ctr657_HtmlModule_lblContent'))

    centers = []
    tag_list = soup.find_all('p')
    tag_list.pop()
    for element in tag_list:
        center = list(element.stripped_strings)
        attributes = {'STATE': 'NY'}
        for line in center:
            if not attributes.get('SHELTER_NAME'):
                attributes['SHELTER_NAME'] = line
            elif not attributes.get('ADDRESS'):
                if any(str(c) in line for c in range(10)):
                    if ', ' in line:
                        line, attributes['CITY'] = line.split(', ')
                    elif '-' in line:
                        line, attributes['CITY'] = line.split('-')
                    attributes['ADDRESS'] = line
                else:
                    continue
            elif not attributes.get('CITY'):
                attributes['CITY'] = line
                break

        centers.append(dict(attributes=attributes))

    return centers

def get_warming_centers_nyc_overnight():
    soup = BeautifulSoup(urlopen(warming['nyc_overnight']), \
        parse_only=SoupStrainer('table', id='content_table'))

    return strip_and_dump(soup, 'p')

def get_warming_centers_nassau():
    soup = BeautifulSoup(urlopen(warming['nassau']), \
        parse_only=SoupStrainer('div', id='container'))

    return strip_and_dump(soup, 'li')

def get_warming_centers_westchester():
    soup = BeautifulSoup(urlopen(warming['westchester']), \
        parse_only=SoupStrainer('div', class_='articleContent'))

    return strip_and_dump(soup, 'li')

def get_fema_shelters():
    url = "http://gis.fema.gov/REST/services/NSS/OpenShelters/MapServer/0/query?where=SHELTER_STATUS+=+%27OPEN%27+and+STATE+=+%27NY%27&returnGeometry=true&outFields=*&f=json"
    json_data = json.load(urlopen(url))

    return json_data['features']


def strip_and_dump(soup, tag):
    centers = []
    for element in soup.find_all(tag):
        center = list(element.stripped_strings)
        # Don't add empty lists
        if center:
            centers.append(center)

    return centers

if __name__ == "__main__":
    #for area in warming:
    #    centers = locals()['get_warming_centers_%s' % area]()
    #    with open('%s_warming.json' % area, 'w') as json_file:
    #        json.dump(centers, json_file)
    shelters = get_fema_shelters()
    shelters.extend(get_warming_centers_nyc())
    shelters.extend(get_warming_centers_suffolk())
    with open('all_warming.json', 'w') as json_file:
        json.dump(shelters, json_file, indent=4)

