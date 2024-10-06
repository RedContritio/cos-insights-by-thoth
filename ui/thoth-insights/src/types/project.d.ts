import { type CoserID, type PhotographerID, type ProjectID, type TimeStamp } from "./base.d";
import { type Photo } from "./photo.d";

export enum ProjectStatus {
  PENDING = 'pending',
  SHOT = 'shot',
  SELECTED = 'selected',
  RETURN_PENDING = 'return_pending',
  RETURNED = 'returned',
  COMPLETED = 'completed',
  UNDEFINED = 'undefined',
}

export class Project {
  id: ProjectID;
  name: string;
  createTime: TimeStamp;
  lastModifiedTime: TimeStamp;
  shootingTime: TimeStamp | null;
  completionTime: TimeStamp | null;
  status: ProjectStatus;
  cosers: CoserID[];
  photographers: PhotographerID[];
  photos: Photo[];

  constructor(id: ProjectID, name: string, createTime: TimeStamp, lastModifiedTime: TimeStamp, shootingTime: TimeStamp | null, completionTime: TimeStamp | null, status: ProjectStatus, cosers: CoserID[], photographers: PhotographerID[], photos: Photo[]) {
    this.id = id;
    this.name = name;
    this.createTime = createTime;
    this.lastModifiedTime = lastModifiedTime;
    this.shootingTime = shootingTime;
    this.completionTime = completionTime;
    this.status = status;
    this.cosers = cosers;
    this.photographers = photographers;
    this.photos = photos;
  }
}

export default Project;