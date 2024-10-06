import { type CoserID, type PhotographerID, type PhotoID, type ProjectID } from "./base.d";

export interface Photo {
  id: PhotoID;

  url: string;
  updateTime: number;

  isLiked: boolean;
  isExcluded: boolean;

  projectID: ProjectID;
  cosers: CoserID[];
  photographers: PhotographerID[];
}